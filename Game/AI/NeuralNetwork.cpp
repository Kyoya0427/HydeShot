//======================================================
// File Name	: NeuralNetwork.cpp
// Summary		: �j���[�����l�b�g���[�N
// Author		: Kyoya  Sakamoto
//======================================================
#include "NeuralNetwork.h"

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

/// <summary>
/// �R���X�g���N�^
/// </summary>
NeuralNetworkLayer::NeuralNetworkLayer()
	: m_numNodes()
	, m_numChildNodes()
	, m_numParentNodes()
	, m_weights()
	, m_weightChanges()
	, m_neuronValues()
	, m_desiredValues()
	, m_errors()
	, m_biasWeights()
	, m_biasValues()
	, m_learningRate()
	, m_linearOutput()
	, m_useMomentum()
	, m_momentumFactor()
	, m_parentLayer()
	, m_childLayer()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="NumNodes">���͑w</param>
/// <param name="parent">�B��w</param>
/// <param name="child">�o�͑w</param>
void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{
	NumNodes;
	//�����������蓖�Ă�
	m_neuronValues  = static_cast<float*>(malloc(sizeof(float) * m_numNodes));
	m_desiredValues = static_cast<float*>(malloc(sizeof(float) * m_numNodes));
	m_errors        = static_cast<float*>(malloc(sizeof(float) * m_numNodes));

	if (parent != nullptr)
	{
		m_parentLayer = parent;
	}

	if (child != nullptr)
	{
		m_childLayer    = child;
		m_weights       = static_cast<float**>(malloc(sizeof(float*) * m_numNodes));
		m_weightChanges = static_cast<float**>(malloc(sizeof(float*) * m_numNodes));

		for (int i = 0; i < m_numNodes; i++)
		{
			m_weights[i]       = static_cast<float*>(malloc(sizeof(float) * m_numChildNodes));
			m_weightChanges[i] = static_cast<float*>(malloc(sizeof(float) * m_numChildNodes));
		}

		m_biasValues  = static_cast<float*>(malloc(sizeof(float) * m_numChildNodes));
		m_biasWeights = static_cast<float*>(malloc(sizeof(float) * m_numChildNodes));
	}
	else 
	{
		m_weights     = nullptr;
		m_biasValues  = nullptr;
		m_biasWeights = nullptr;
	}

	//���ׂĂɃ[�����܂܂�Ă��邱�Ƃ��m�F
	for (int i = 0; i < m_numNodes; i++)
	{
		if (m_neuronValues)
			m_neuronValues[i] = 0.0f;
		if (m_desiredValues)
			m_desiredValues[i] = 0.0f;
		if (m_errors)
			m_errors[i] = 0.0f;

		if (m_childLayer != nullptr)
		{
			for (int j = 0; j < m_numChildNodes; j++)
			{
				if (m_weights)
					m_weights[i][j] = 0.0f;
				if (m_weightChanges)
					m_weightChanges[i][j] = 0.0f;
			}
		}
	}

	if (m_childLayer != nullptr)
	{
		for (int j = 0; j < m_numChildNodes; j++)
		{
			if (m_biasValues)
				m_biasValues[j] = -1.0f;
			if (m_biasWeights)
				m_biasWeights[j] = 0.0f;
		}
	}
}

/// <summary>
/// �������[���
/// </summary>
void NeuralNetworkLayer::CleanUp()
{
	free(m_neuronValues);
	free(m_desiredValues);
	free(m_errors);

	if (m_weights != nullptr)
	{
		for (int i = 0; i < m_numNodes; i++)
		{
			free(m_weights[i]);
			free(m_weightChanges[i]);
		}

		free(m_weights);
		free(m_weightChanges);
	}

	if (m_biasValues != nullptr)
		free(m_biasValues);
	if (m_biasWeights != nullptr)
		free(m_biasWeights);
}

/// <summary>
/// �w�K���J�n����Ƃ������Ă�
/// </summary>
void NeuralNetworkLayer::RandomizeWeights()
{
	float	min = -1.0f;
	float	max =  1.0f;

	std::random_device seed;
	std::mt19937 random(seed());

	std::uniform_real_distribution<float> dist(min, std::nextafter(max, FLT_MAX));
	
	for (int i = 0; i < m_numNodes; i++)
	{
		for (int j = 0; j < m_numChildNodes; j++)
		{
			m_weights[i][j] = dist(random);
		}
	}

	for (int j = 0; j < m_numChildNodes; j++) 
	{
		m_biasWeights[j] = dist(random);
	}
}

/// <summary>
/// �G���[�����������ꂼ��ɑ��
/// </summary>
void NeuralNetworkLayer::CalculateErrors()
{
	float	sum = 0.0;
	// �o�͑w(output layer)
	if (m_childLayer == nullptr)
	{
		for (int i = 0; i < m_numNodes; i++) 
		{
			m_errors[i] = (m_desiredValues[i] - m_neuronValues[i]) * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	} // ���͑w(input layer)
	else if (m_parentLayer == nullptr)
	{
		for (int i = 0; i < m_numNodes; i++)
		{
			m_errors[i] = 0.0f;
		}
	} // �B��w(hidden layer)
	else
	{
		for (int i = 0; i < m_numNodes; i++) 
		{
			sum = 0.0f;
			for (int j = 0; j < m_numChildNodes; j++)
			{
				sum += m_childLayer->m_errors[j] * m_weights[i][j];
			}

			m_errors[i] = sum * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	}
}

/// <summary>
/// �d�݂𒲐�
/// </summary>
void NeuralNetworkLayer::AdjustWeights()
{
	float	dw = 0.0;
	if (m_childLayer != nullptr) 
	{
		for (int i = 0; i < m_numNodes; i++)
		{
			for (int j = 0; j < m_numChildNodes; j++)
			{
				dw = m_learningRate * m_childLayer->m_errors[j] * m_neuronValues[i];
				m_weights[i][j] += dw + m_momentumFactor * m_weightChanges[i][j];
				m_weightChanges[i][j] = dw;
			}
		}

		for (int j = 0; j < m_numChildNodes; j++)
		{
			m_biasWeights[j] += m_learningRate * m_childLayer->m_errors[j] * m_biasValues[j];
		}
	}
}

/// <summary>
/// �S�Ă̏d�݂̌v�Z
/// </summary>
void NeuralNetworkLayer::CalculateNeuronValues()
{
	float x;
	if (m_parentLayer != nullptr)
	{
		for (int j = 0; j < m_numNodes; j++)
		{
			x = 0;
			for (int i = 0; i < m_numParentNodes; i++)
			{
				x += m_parentLayer->m_neuronValues[i] * m_parentLayer->m_weights[i][j];
			}
			x += m_parentLayer->m_biasValues[j] * m_parentLayer->m_biasWeights[j];

			if ((m_childLayer == nullptr) && m_linearOutput)
				m_neuronValues[j] = x;
			else
				m_neuronValues[j] = 1.0f / (1.0f + static_cast<float>(exp(-x)));
		}
	}
}




/// <summary>
/// ������
/// </summary>
/// <param name="NumNodes">���͑w</param>
/// <param name="parent">�B��w</param>
/// <param name="child">�o�͑w</param>
void NeuralNetwork::Initialize(int nodesInput, int nodesHidden, int nodesOutput)
{
	m_inputLayer.m_numNodes       = nodesInput;
	m_inputLayer.m_numChildNodes  = nodesHidden;
	m_inputLayer.m_numParentNodes = 0;
	m_inputLayer.Initialize(nodesInput, nullptr, &m_hiddenLayer);
	m_inputLayer.RandomizeWeights();

	m_hiddenLayer.m_numNodes       = nodesHidden;
	m_hiddenLayer.m_numChildNodes  = nodesOutput;
	m_hiddenLayer.m_numParentNodes = nodesInput;
	m_hiddenLayer.Initialize(nodesHidden, &m_inputLayer, &m_outputLayer);
	m_hiddenLayer.RandomizeWeights();

	m_outputLayer.m_numNodes       = nodesOutput;
	m_outputLayer.m_numChildNodes  = 0;
	m_outputLayer.m_numParentNodes = nodesHidden;
	m_outputLayer.Initialize(nodesOutput, &m_hiddenLayer, nullptr);
}

/// <summary>
/// �������[���
/// </summary>
void NeuralNetwork::CleanUp()
{
	m_inputLayer.CleanUp();
	m_hiddenLayer.CleanUp();
	m_outputLayer.CleanUp();
}

/// <summary>
/// ���͂�ݒ�
/// </summary>
/// <param name="i">�w��</param>
/// <param name="value">���͂���l</param>
void NeuralNetwork::SetInput(int i, float value)
{
	if ((i >= 0) && (i < m_inputLayer.m_numNodes))
	{
		m_inputLayer.m_neuronValues[i] = value;
	}
}

/// <summary>
/// �o�͒l
/// </summary>
/// <param name="i">�w��</param>
/// <returns>�o�̓f�[�^</returns>
float NeuralNetwork::GetOutput(int i)
{
	if ((i >= 0) && (i < m_outputLayer.m_numNodes))
	{
		return m_outputLayer.m_neuronValues[i];
	}
	return (float)INT_MAX; // to indicate an error
}

/// <summary>
/// �]�܂����l��ݒ�
/// </summary>
/// <param name="i">�v�f�ԍ�</param>
/// <param name="value">�l</param>
void NeuralNetwork::SetDesiredOutput(int i, float value)
{
	if ((i >= 0) && (i < m_outputLayer.m_numNodes)) 
	{
		m_outputLayer.m_desiredValues[i] = value;
	}
}

/// <summary>
/// �d�݂̌v�Z
/// </summary>
void NeuralNetwork::FeedForward()
{
	m_inputLayer.CalculateNeuronValues();
	m_hiddenLayer.CalculateNeuronValues();
	m_outputLayer.CalculateNeuronValues();
}

/// <summary>
/// �o�͑w�ƉB��w�̃G���[�����Ƃɓ��͒l�ƉB��w�̏d�݂𒲐�
/// </summary>
void NeuralNetwork::BackPropagate()
{
	m_outputLayer.CalculateErrors();
	m_hiddenLayer.CalculateErrors();

	m_hiddenLayer.AdjustWeights();
	m_inputLayer.AdjustWeights();
}

/// <summary>
/// �o�͑w�̂����Ƃ��������̂𔻒f����
/// </summary>
/// <returns>�����Ƃ������l��Ԃ�</returns>
int	NeuralNetwork::GetMaxOutputID()
{
	float maxval = m_outputLayer.m_neuronValues[0];
	int id = 0;

	for (int i = 1; i < m_outputLayer.m_numNodes; i++) 
	{
		if (m_outputLayer.m_neuronValues[i] > maxval)
		{
			maxval = m_outputLayer.m_neuronValues[i];
			id = i;
		}
	}
	return id;
}

/// <summary>
/// �o�͒l�Ɩ]�܂����l�̏W���Ɋ֌W����G���[
/// </summary>
/// <returns>�G���[��Ԃ�</returns>
float NeuralNetwork::CalculateError()
{
	float	error = 0.0;

	for (int i = 0; i < m_outputLayer.m_numNodes; i++) 
	{
		error += static_cast<float>(pow(m_outputLayer.m_neuronValues[i] - m_outputLayer.m_desiredValues[i], 2));
	}
	error = error / m_outputLayer.m_numNodes;
	return error;
}

/// <summary>
/// �w�K����ݒ�
/// </summary>
/// <param name="rate">�w�K��</param>
void NeuralNetwork::SetLearningRate(float rate)
{
	m_inputLayer.m_learningRate  = rate;
	m_hiddenLayer.m_learningRate = rate;
	m_outputLayer.m_learningRate = rate;
}

/// <summary>
/// ���`�������֐����g�����ݒ�
/// </summary>
/// <param name="useLinear">true�Ŏg��</param>
void NeuralNetwork::SetLinearOutput(bool linear)
{
	m_inputLayer.m_linearOutput  = linear;
	m_hiddenLayer.m_linearOutput = linear;
	m_outputLayer.m_linearOutput = linear;
}

/// <summary>
/// ���[�����g���g�����ƑO�q���[�����^��������ݒ�
/// </summary>
/// <param name="m_useMomentum">true�Ŏg��</param>
/// <param name="factor">���q</param>
void NeuralNetwork::SetMomentum(bool momentum, float factor)
{
	m_inputLayer.m_useMomentum     = momentum;
	m_hiddenLayer.m_useMomentum    = momentum;
	m_outputLayer.m_useMomentum    = momentum;

	m_inputLayer.m_momentumFactor  = factor;
	m_hiddenLayer.m_momentumFactor = factor;
	m_outputLayer.m_momentumFactor = factor;
}

/// <summary>
/// �f�[�^���o��
/// </summary>
/// <param name="filename">�t�@�C���l�[��</param>
void NeuralNetwork::DumpData(char* filename)
{
	FILE* f;
	
	errno_t error;
	error = fopen_s(&f,filename, "w");
	//input
	//Node Values		
	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
		fprintf(f, "%f,",  m_inputLayer.m_neuronValues[i]);
	fprintf(f, "\n");

	//Weights
	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
		for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
			fprintf(f, " %f,", m_inputLayer.m_weights[i][j]);
	fprintf(f, "\n");

	//Bias Weights
	for (int i = 0; i < m_inputLayer.m_numChildNodes; i++)
		fprintf(f, " %f,", m_inputLayer.m_biasWeights[i]);
	fprintf(f, "\n");

	//hidden
	//Weights
	for (int i = 0; i < m_hiddenLayer.m_numNodes; i++)
		for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
			fprintf(f, "%f,", m_hiddenLayer.m_weights[i][j]);
	fprintf(f, "\n");

	//Bias Weights
	for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
		fprintf(f, "%f,", m_hiddenLayer.m_biasWeights[j]);
	fprintf(f, "\n");

	//Output
	//Node Values
	for (int i = 0; i < m_outputLayer.m_numNodes; i++)
		fprintf(f, "%f,", m_outputLayer.m_neuronValues[i]);
	fprintf(f, "\n");

	fclose(f);
}

/// <summary>
/// �w�K�f�[�^�����
/// </summary>
/// <param name="filename">�t�@�C���l�[��</param>
void NeuralNetwork::LearningDataInput(char* filename)
{
	std::wstring str;
	// �t�@�C���̃I�[�v��
	std::wifstream ifs(filename);

	std::vector<std::vector<float>> tempData = std::vector<std::vector<float>>(6, std::vector<float>(120, 0.0f));

	for (int i = 0; i < 6; i++)
	{
		int j = 0;
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		while (std::getline(stream, tmp, L','))
		{
			tempData[i][j] = std::stof(tmp);
			j++;
		}
	}


	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
	{
		m_inputLayer.m_neuronValues[i] = tempData[0][i];
	}

	{
		int num = 0;
		for (int i = 0; i < m_inputLayer.m_numNodes; i++)
		{
			for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
			{
				m_inputLayer.m_weights[i][j] = tempData[1][num];
				num++;
			}
		}
	}
	
	for (int i = 0; i < m_inputLayer.m_numChildNodes; i++)
	{
		m_inputLayer.m_biasWeights[i] = tempData[2][i];
	}

	{
		int num = 0;
		for (int i = 0; i < m_hiddenLayer.m_numNodes; i++)
		{
			for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
			{
				m_hiddenLayer.m_weights[i][j] = tempData[3][num];
				num++;
			}
		}
	}

	for (int i = 0; i < m_hiddenLayer.m_numChildNodes; i++)
	{
		m_hiddenLayer.m_biasWeights[i] = tempData[4][i];
	}
	
	for (int i = 0; i < m_outputLayer.m_numNodes; i++)
	{
		m_outputLayer.m_neuronValues[i] = tempData[5][i];
	}

}