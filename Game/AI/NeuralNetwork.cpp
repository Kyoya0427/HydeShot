//======================================================
// File Name	: NeuralNetworkLayer.cpp
// Summary		: ニューラルネットワーク
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "NeuralNetwork.h"

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>




//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Neural Networks, Chapter 14
*/
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetworkLayer Class
/////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// コンストラクタ
/// </summary>
NeuralNetworkLayer::NeuralNetworkLayer()
{
	m_parentLayer    = NULL;
	m_childLayer     = NULL;
	m_linearOutput   = false;
	m_useMomentum    = false;
	m_momentumFactor = 0.9;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="NumNodes">入力層</param>
/// <param name="parent">隠れ層</param>
/// <param name="child">出力層</param>
void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{
	NumNodes;
	// Allocate memory
	m_neuronValues  = (float*)malloc(sizeof(float) * m_numNodes);
	m_desiredValues = (float*)malloc(sizeof(float) * m_numNodes);
	m_errors        = (float*)malloc(sizeof(float) * m_numNodes);

	if (parent != NULL)
	{
		m_parentLayer = parent;
	}

	if (child != NULL)
	{
		m_childLayer    = child;
		m_weights       = (float**)malloc(sizeof(float*) * m_numNodes);
		m_weightChanges = (float**)malloc(sizeof(float*) * m_numNodes);

		for (int i = 0; i < m_numNodes; i++)
		{
			m_weights[i]       = (float*)malloc(sizeof(float) * m_numChildNodes);
			m_weightChanges[i] = (float*)malloc(sizeof(float) * m_numChildNodes);
		}

		m_biasValues  = (float*)malloc(sizeof(float) * m_numChildNodes);
		m_biasWeights = (float*)malloc(sizeof(float) * m_numChildNodes);
	}
	else 
	{
		m_weights     = NULL;
		m_biasValues  = NULL;
		m_biasWeights = NULL;
	}

	// Make sure everything contains zeros
	for (int i = 0; i < m_numNodes; i++) 
	{
		m_neuronValues[i]  = 0;
		m_desiredValues[i] = 0;
		m_errors[i]        = 0;

		if (m_childLayer != NULL)
		{
			for (int j = 0; j < m_numChildNodes; j++) 
			{
				m_weights[i][j]       = 0;
				m_weightChanges[i][j] = 0;
			}
		}
	}

	if (m_childLayer != NULL) 
	{
		for (int j = 0; j < m_numChildNodes; j++) 
		{
			m_biasValues[j]  = -1;
			m_biasWeights[j] = 0;
		}
	}
}

/// <summary>
/// メモリー解放
/// </summary>
void NeuralNetworkLayer::CleanUp(void)
{
	free(m_neuronValues);
	free(m_desiredValues);
	free(m_errors);

	if (m_weights != NULL)
	{
		for (int i = 0; i < m_numNodes; i++)
		{
			free(m_weights[i]);
			free(m_weightChanges[i]);
		}

		free(m_weights);
		free(m_weightChanges);
	}

	if (m_biasValues != NULL)
		free(m_biasValues);
	if (m_biasWeights != NULL)
		free(m_biasWeights);
}

/// <summary>
/// 学習を開始するときだけ呼ぶ
/// </summary>
void NeuralNetworkLayer::RandomizeWeights(void)
{
	int	min = 0;
	int	max = 200;
	int	number;

	srand((unsigned)time(NULL));

	for (int i = 0; i < m_numNodes; i++)
	{
		for (int j = 0; j < m_numChildNodes; j++)
		{
			number = (((abs(rand()) % (max - min + 1)) + min));
			if (number > max)
				number = max;
			if (number < min)
				number = min;

			m_weights[i][j] = number / 100.0f - 1;
		}
	}

	for (int j = 0; j < m_numChildNodes; j++) 
	{
		number = (((abs(rand()) % (max - min + 1)) + min));
		if (number > max)
			number = max;
		if (number < min)
			number = min;
		m_biasWeights[j] = number / 100.0f - 1;
	}
}

/// <summary>
/// エラー方程式をそれぞれに代入
/// </summary>
void NeuralNetworkLayer::CalculateErrors(void)
{
	float	sum = 0.0;
	// 出力層(output layer)
	if (m_childLayer == NULL)
	{
		for (int i = 0; i < m_numNodes; i++) 
		{
			m_errors[i] = (m_desiredValues[i] - m_neuronValues[i]) * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	} // 入力層(input layer)
	else if (m_parentLayer == NULL)
	{
		for (int i = 0; i < m_numNodes; i++)
		{
			m_errors[i] = 0.0f;
		}
	} // 隠れ層(hidden layer)
	else
	{
		for (int i = 0; i < m_numNodes; i++) 
		{
			sum = 0;
			for (int j = 0; j < m_numChildNodes; j++)
			{
				sum += m_childLayer->m_errors[j] * m_weights[i][j];
			}

			m_errors[i] = sum * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	}
}

/// <summary>
/// 重みを調整
/// </summary>
void NeuralNetworkLayer::AdjustWeights(void)
{
	float	dw = 0.0;
	if (m_childLayer != NULL) 
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
/// 全ての重みの計算
/// </summary>
void NeuralNetworkLayer::CalculateNeuronValues(void)
{
	float	x;
	if (m_parentLayer != NULL)
	{
		for (int j = 0; j < m_numNodes; j++)
		{
			x = 0;
			for (int i = 0; i < m_numParentNodes; i++)
			{
				x += m_parentLayer->m_neuronValues[i] * m_parentLayer->m_weights[i][j];
			}
			x += m_parentLayer->m_biasValues[j] * m_parentLayer->m_biasWeights[j];

			if ((m_childLayer == NULL) && m_linearOutput)
				m_neuronValues[j] = x;
			else
				m_neuronValues[j] = 1.0f / (1.0f + static_cast<float>(exp(-x)));
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetwork Class
/////////////////////////////////////////////////////////////////////////////////////////////////


/// <summary>
/// 初期化
/// </summary>
/// <param name="NumNodes">入力層</param>
/// <param name="parent">隠れ層</param>
/// <param name="child">出力層</param>
void NeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
{
	m_inputLayer.m_numNodes       = nNodesInput;
	m_inputLayer.m_numChildNodes  = nNodesHidden;
	m_inputLayer.m_numParentNodes = 0;
	m_inputLayer.Initialize(nNodesInput, NULL, &m_hiddenLayer);
	m_inputLayer.RandomizeWeights();

	m_hiddenLayer.m_numNodes       = nNodesHidden;
	m_hiddenLayer.m_numChildNodes  = nNodesOutput;
	m_hiddenLayer.m_numParentNodes = nNodesInput;
	m_hiddenLayer.Initialize(nNodesHidden, &m_inputLayer, &m_outputLayer);
	m_hiddenLayer.RandomizeWeights();

	m_outputLayer.m_numNodes       = nNodesOutput;
	m_outputLayer.m_numChildNodes  = 0;
	m_outputLayer.m_numParentNodes = nNodesHidden;
	m_outputLayer.Initialize(nNodesOutput, &m_hiddenLayer, NULL);
}

/// <summary>
/// メモリー解放
/// </summary>
void NeuralNetwork::CleanUp()
{
	m_inputLayer.CleanUp();
	m_hiddenLayer.CleanUp();
	m_outputLayer.CleanUp();
}

/// <summary>
/// 入力を設定
/// </summary>
/// <param name="i">指数</param>
/// <param name="value">入力する値</param>
void NeuralNetwork::SetInput(int i, float value)
{
	if ((i >= 0) && (i < m_inputLayer.m_numNodes))
	{
		m_inputLayer.m_neuronValues[i] = value;
	}
}

/// <summary>
/// 出力値
/// </summary>
/// <param name="i">指数</param>
/// <returns></returns>
float NeuralNetwork::GetOutput(int i)
{
	if ((i >= 0) && (i < m_outputLayer.m_numNodes))
	{
		return m_outputLayer.m_neuronValues[i];
	}
	return (float)INT_MAX; // to indicate an error
}

/// <summary>
/// 望ましい値を設定
/// </summary>
/// <param name="i"></param>
/// <param name="value"></param>
void NeuralNetwork::SetDesiredOutput(int i, float value)
{
	if ((i >= 0) && (i < m_outputLayer.m_numNodes)) 
	{
		m_outputLayer.m_desiredValues[i] = value;
	}
}

/// <summary>
/// 重みの計算
/// </summary>
void NeuralNetwork::FeedForward(void)
{
	m_inputLayer.CalculateNeuronValues();
	m_hiddenLayer.CalculateNeuronValues();
	m_outputLayer.CalculateNeuronValues();
}

/// <summary>
/// 出力層と隠れ層のエラーをもとに入力値と隠れ層の重みを調整
/// </summary>
void NeuralNetwork::BackPropagate(void)
{
	m_outputLayer.CalculateErrors();
	m_hiddenLayer.CalculateErrors();

	m_hiddenLayer.AdjustWeights();
	m_inputLayer.AdjustWeights();
}

/// <summary>
/// 出力層のもっとも高いものを判断する
/// </summary>
/// <returns>もっとも高い値を返す</returns>
int	NeuralNetwork::GetMaxOutputID(void)
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
/// 出力値と望ましい値の集合に関係するエラー
/// </summary>
/// <returns><エラーを返す/returns>
float NeuralNetwork::CalculateError(void)
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
/// 学習率を設定
/// </summary>
/// <param name="rate">学習率</param>
void NeuralNetwork::SetLearningRate(float rate)
{
	m_inputLayer.m_learningRate  = rate;
	m_hiddenLayer.m_learningRate = rate;
	m_outputLayer.m_learningRate = rate;
}

/// <summary>
/// 線形活性化関数を使うか設定
/// </summary>
/// <param name="useLinear"></param>
void NeuralNetwork::SetLinearOutput(bool useLinear)
{
	m_inputLayer.m_linearOutput  = useLinear;
	m_hiddenLayer.m_linearOutput = useLinear;
	m_outputLayer.m_linearOutput = useLinear;
}

/// <summary>
/// モーメントを使うかと前述モーメンタム因数を設定
/// </summary>
/// <param name="m_useMomentum"></param>
/// <param name="factor"></param>
void NeuralNetwork::SetMomentum(bool useMomentum, float factor)
{
	m_inputLayer.m_useMomentum     = useMomentum;
	m_hiddenLayer.m_useMomentum    = useMomentum;
	m_outputLayer.m_useMomentum    = useMomentum;

	m_inputLayer.m_momentumFactor  = factor;
	m_hiddenLayer.m_momentumFactor = factor;
	m_outputLayer.m_momentumFactor = factor;
}

/// <summary>
/// データを出力
/// </summary>
/// <param name="filename"></param>
void NeuralNetwork::DumpData(char* filename)
{
	FILE* f;
	
	errno_t error;
	error = fopen_s(&f,filename, "w");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Input Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
		fprintf(f, "(%d) = %f\n", i, m_inputLayer.m_neuronValues[i]);
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
		for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, m_inputLayer.m_weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, m_inputLayer.m_biasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Hidden Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for (int i = 0; i < m_hiddenLayer.m_numNodes; i++)
		for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, m_hiddenLayer.m_weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, m_hiddenLayer.m_biasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Output Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for (int i = 0; i < m_outputLayer.m_numNodes; i++)
		fprintf(f, "(%d) = %f\n", i, m_outputLayer.m_neuronValues[i]);
	fprintf(f, "\n");

	fclose(f);
}

///// <summary>
///// コンストラクタ
///// </summary>
//NeuralNetwork::NeuralNetworkLayer::NeuralNetworkLayer()
//{
//	m_parentLayer    = NULL;
//	m_m_childLayer     = NULL;
//	m_linearOutput   = false;
//	m_useMomentum    = false;
//	m_momentumFactor = 0.9;
//}
//
///// <summary>
///// 初期化
///// </summary>
///// <param name="NumNodes">入力層</param>
///// <param name="parent">隠れ層</param>
///// <param name="child">出力層</param>
//void NeuralNetwork::NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetwork::NeuralNetworkLayer* parent, NeuralNetwork::NeuralNetworkLayer* child)
//{
//	NumNodes;
//	// Allocate memory
//	m_neuronValues  = std::make_unique<DataType[]>(m_numNodes);
//	m_desiredValues = std::make_unique<DataType[]>(m_numNodes);
//	m_errors        = std::make_unique<DataType[]>(m_numNodes);
//
//	if (parent != NULL)
//	{
//		m_parentLayer = parent;
//	}
//
//	if (child != NULL)
//	{
//		m_m_childLayer    = child;
//		m_weights       = std::make_unique<DataArray[]>(m_numNodes);
//		m_weightChanges = std::make_unique<DataArray[]>(m_numNodes);
//
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			m_weights[i]       = std::make_unique<DataType[]>(m_numChildNodes);
//			m_weightChanges[i] = std::make_unique<DataType[]>(m_numChildNodes);
//		}
//		m_biasWeights = std::make_unique<DataType[]>(m_numChildNodes);
//		m_biasValues  = std::make_unique<DataType[]>(m_numChildNodes);
//	}
//	else
//	{
//		m_weights     = NULL;
//		m_biasValues  = NULL;
//		m_biasWeights = NULL;
//	}
//
//	// Make sure everything contains zeros
//	for (int i = 0; i < m_numNodes; i++)
//	{
//		m_neuronValues[i]  = 0;
//		m_desiredValues[i] = 0;
//		m_errors[i]        = 0;
//
//		if (m_m_childLayer != NULL)
//		{
//			for (int j = 0; j < m_numChildNodes; j++)
//			{
//				m_weights[i][j]       = 0;
//				m_weightChanges[i][j] = 0;
//			}
//		}
//	}
//
//	if (m_m_childLayer != NULL)
//	{
//		for (int j = 0; j < m_numChildNodes; j++)
//		{
//			m_biasValues[j]  = -1;
//			m_biasWeights[j] = 0;
//		}
//	}
//}
//
///// <summary>
///// メモリー解放
///// </summary>
//void NeuralNetwork::NeuralNetworkLayer::CleanUp()
//{
//	m_neuronValues.release();
//	m_desiredValues.release();
//	m_errors.release();
//
//	if (!m_weights.get()) 
//	{
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			m_weights[i].release();
//			m_weightChanges[i].release();
//		}
//		m_weights.release();
//		m_weightChanges.release();
//	}
//
//	if (!m_biasValues.get())
//		m_biasValues.release();
//	if (!m_biasWeights.get())
//		m_biasWeights.release();
//}
//
///// <summary>
///// 学習を開始するときだけ呼ぶ
///// </summary>
//void NeuralNetwork::NeuralNetworkLayer::RandomizeWeights()
//{
//	int	min = 0;
//	int	max = 200;
//	int	number;
//
//	srand((unsigned)time(NULL));
//
//	for (int i = 0; i < m_numNodes; i++)
//	{
//		for (int j = 0; j < m_numChildNodes; j++)
//		{
//			number = (((abs(rand()) % (max - min + 1)) + min));
//			if (number > max)
//				number = max;
//			if (number < min)
//				number = min;
//
//			m_weights[i][j] = number / 100.0f - 1;
//		}
//	}
//
//	for (int j = 0; j < m_numChildNodes; j++)
//	{
//		number = (((abs(rand()) % (max - min + 1)) + min));
//		if (number > max)
//			number = max;
//		if (number < min)
//			number = min;
//
//		m_biasWeights[j] = number / 100.0f - 1;
//	}
//
//}
//
///// <summary>
///// エラー方程式をそれぞれに代入
///// </summary>
//void NeuralNetwork::NeuralNetworkLayer::CalculateErrors()
//{
//	DataType* neuronValues  = &m_neuronValues[0];
//	DataType* desiredValues = &m_desiredValues[0];
//	DataType* errors        = &m_errors[0];
//
//	DataType	sum = 0.0;
//
//	// 出力層(output layer)
//	if (m_m_childLayer == NULL)
//	{
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			errors[i] = (desiredValues[i] - neuronValues[i]) * neuronValues[i] * (1.0f - desiredValues[i]);
//		}
//	}
//	// 入力層(input layer)
//	else if (m_parentLayer == NULL)
//	{
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			errors[i] = 0.0f;
//		}
//	}
//	// 隠れ層(hidden layer)
//	else {
//		DataType* weights = NULL;
//		DataType* m_childLayerErrors = &(m_m_childLayer->m_errors[0]);
//
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			sum = 0;
//			weights = &m_weights[i][0];
//			for (int j = 0; j < m_numChildNodes; j++)
//			{
//				sum += m_childLayerErrors[j] * weights[j];
//			}
//
//			m_errors[i] = sum * neuronValues[i] * (1.0f - neuronValues[i]);
//		}
//	}
//
//}
//
///// <summary>
///// 重みを調整
///// </summary>
//void NeuralNetwork::NeuralNetworkLayer::AdjustWeights()
//{
//	DataType* weights;
//	DataType* weightChanges;
//	DataType* neuronValues  = &m_neuronValues[0];
//	DataType* desiredValues = &m_desiredValues[0];
//	DataType* errors        = &m_errors[0];
//	DataType* biasWeights   = &m_biasWeights[0];
//	DataType* biasValues    = &m_biasValues[0];
//	DataType	dw          = 0.0;
//
//	errors;
//	desiredValues;
//
//	if (m_m_childLayer != NULL)
//	{
//		for (int i = 0; i < m_numNodes; i++) 
//		{
//			weights = &m_weights[i][0];
//			weightChanges = &m_weightChanges[i][0];
//
//			for (int j = 0; j < m_numChildNodes; j++) 
//			{
//				dw               = m_learningRate * m_m_childLayer->m_errors[j] * neuronValues[i];
//				weights[j]      += dw + m_momentumFactor * weightChanges[j];
//				weightChanges[j] = dw;
//			}
//		}
//
//		DataType* m_childLayerErrors = &(m_m_childLayer->m_errors[0]);
//
//		for (int j = 0; j < m_numChildNodes; j++) 
//		{
//			biasWeights[j] += m_learningRate * m_childLayerErrors[j] * biasValues[j];
//		}
//	}
//}
//
///// <summary>
///// 全ての重みの計算
///// </summary>
//void NeuralNetwork::NeuralNetworkLayer::CalculateNeuronValues()
//{
//	DataType	x;
//	if (m_parentLayer != NULL)
//	{
//		for (int j = 0; j < m_numNodes; j++)
//		{
//			x = 0;
//
//			for (int i = 0; i < m_numParentNodes; i++)
//			{
//				x += m_parentLayer->m_neuronValues[i] * m_parentLayer->m_weights[i][j];
//			}
//
//			x += m_parentLayer->m_biasValues[j] * m_parentLayer->m_biasWeights[j];
//
//			if ((m_m_childLayer == NULL) && m_linearOutput)
//				m_neuronValues[j] = x;
//			else
//				m_neuronValues[j] = 1.0f / (1.0f + exp(-x));
//		}
//	}
//}
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//// NeuralNetwork Class
///////////////////////////////////////////////////////////////////////////////////////////////////
//
///// <summary>
///// 初期化
///// </summary>
///// <param name="NumNodes">入力層</param>
///// <param name="parent">隠れ層</param>
///// <param name="child">出力層</param>
//void NeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
//{
//	
//	m_inputLayer.m_numNodes = nNodesInput;
//	m_inputLayer.m_numChildNodes = nNodesHidden;
//	m_inputLayer.m_numParentNodes = 0;
//	m_inputLayer.Initialize(nNodesInput, NULL, &m_hiddenLayer);
//	m_inputLayer.RandomizeWeights();
//
//	m_hiddenLayer.m_numNodes = nNodesHidden;
//	m_hiddenLayer.m_numChildNodes = nNodesOutput;
//	m_hiddenLayer.m_numParentNodes = nNodesInput;
//	m_hiddenLayer.Initialize(nNodesHidden, &m_inputLayer, &m_outputLayer);
//	m_hiddenLayer.RandomizeWeights();
//
//	m_outputLayer.m_numNodes = nNodesOutput;
//	m_outputLayer.m_numChildNodes = 0;
//	m_outputLayer.m_numParentNodes = nNodesHidden;
//	m_outputLayer.Initialize(nNodesOutput, &m_hiddenLayer, NULL);
//}
//
///// <summary>
///// メモリー解放
///// </summary>
//void NeuralNetwork::CleanUp()
//{
//	m_inputLayer.CleanUp();
//	m_hiddenLayer.CleanUp();
//	m_outputLayer.CleanUp();
//}
//
///// <summary>
///// 入力を設定
///// </summary>
///// <param name="i">指数</param>
///// <param name="value">入力する値</param>
//void NeuralNetwork::SetInput(int i, float value)
//{
//	if ((i >= 0) && (i < m_inputLayer.m_numNodes)) 
//	{
//		m_inputLayer.m_neuronValues[i] = value;
//	}
//}
//
///// <summary>
///// 出力値
///// </summary>
///// <param name="i">指数</param>
///// <returns></returns>
//float	NeuralNetwork::GetOutput(int i)
//{
//	if ((i >= 0) && (i < m_outputLayer.m_numNodes)) 
//	{
//		return m_outputLayer.m_neuronValues[i];
//	}
//
//	return (float)INT_MAX; // to indicate an error
//}
//
///// <summary>
///// 望ましい値を設定
///// </summary>
///// <param name="i"></param>
///// <param name="value"></param>
//void NeuralNetwork::SetDesiredOutput(int i, float value)
//{
//	if ((i >= 0) && (i < m_outputLayer.m_numNodes))
//	{
//		m_outputLayer.m_desiredValues[i] = value;
//	}
//}
//
///// <summary>
///// 重みの計算
///// </summary>
//void NeuralNetwork::FeedForward()
//{
//	m_inputLayer.CalculateNeuronValues();
//	m_hiddenLayer.CalculateNeuronValues();
//	m_outputLayer.CalculateNeuronValues();
//}
//
///// <summary>
///// 出力層と隠れ層のエラーをもとに入力値と隠れ層の重みを調整
///// </summary>
//void NeuralNetwork::BackPropagate()
//{
//	m_outputLayer.CalculateErrors();
//	m_hiddenLayer.CalculateErrors();
//
//	m_hiddenLayer.AdjustWeights();
//	m_inputLayer.AdjustWeights();
//}
//
///// <summary>
///// 出力層のもっとも高いものを判断する
///// </summary>
///// <returns>もっとも高い値を返す</returns>
//int	NeuralNetwork::GetMaxOutputID()
//{
//	float maxval = m_outputLayer.m_neuronValues[0];
//	int id       = 0;
//
//	for (int i = 1; i < m_outputLayer.m_numNodes; i++) 
//	{
//		if (m_outputLayer.m_neuronValues[i] > maxval) 
//		{
//			maxval = m_outputLayer.m_neuronValues[i];
//			id     = i;
//		}
//	}
//	return id;
//}
//
///// <summary>
///// 出力値と望ましい値の集合に関係するエラー
///// </summary>
///// <returns><エラーを返す/returns>
//float NeuralNetwork::CalculateError()
//{
//	float	error = 0.0;
//
//	for (int i = 0; i < m_outputLayer.m_numNodes; i++)
//	{
//		error += pow(m_outputLayer.m_neuronValues[i] - m_outputLayer.m_desiredValues[i], 2);
//	}
//
//	error = error / m_outputLayer.m_numNodes;
//	return error;
//}
//
///// <summary>
///// 学習率を設定
///// </summary>
///// <param name="rate">学習率</param>
//void NeuralNetwork::SetLearningRate(float rate)
//{
//	m_inputLayer.m_learningRate = rate;
//	m_hiddenLayer.m_learningRate = rate;
//	m_outputLayer.m_learningRate = rate;
//}
//
///// <summary>
///// 線形活性化関数を使うか設定
///// </summary>
///// <param name="useLinear"></param>
//void NeuralNetwork::SetLinearOutput(bool useLinear)
//{
//	m_inputLayer.m_linearOutput = useLinear;
//	m_hiddenLayer.m_linearOutput = useLinear;
//	m_outputLayer.m_linearOutput = useLinear;
//}
//
///// <summary>
///// モーメントを使うかと前述モーメンタム因数を設定
///// </summary>
///// <param name="m_useMomentum"></param>
///// <param name="factor"></param>
//void NeuralNetwork::SetMomentum(bool m_useMomentum, float factor)
//{
//	m_inputLayer.m_useMomentum = m_useMomentum;
//	m_hiddenLayer.m_useMomentum = m_useMomentum;
//	m_outputLayer.m_useMomentum = m_useMomentum;
//
//	m_inputLayer.m_momentumFactor = factor;
//	m_hiddenLayer.m_momentumFactor = factor;
//	m_outputLayer.m_momentumFactor = factor;
//}
//
///// <summary>
///// データを出力
///// </summary>
///// <param name="filename"></param>
//void NeuralNetwork::DumpData(char* filename)
//{
//	FILE* f;
//
//	errno_t error;
//	error = fopen_s(&f,filename, "w");
//
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "Input Layer\n");
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "\n");
//	fprintf(f, "Node Values:\n");
//	fprintf(f, "\n");
//	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
//		fprintf(f, "(%d) = %f\n", i, m_inputLayer.m_neuronValues[i]);
//	fprintf(f, "\n");
//	fprintf(f, "Weights:\n");
//	fprintf(f, "\n");
//	for (int i = 0; i < m_inputLayer.m_numNodes; i++)
//		for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
//			fprintf(f, "(%d, %d) = %f\n", i, j, m_inputLayer.m_weights[i][j]);
//	fprintf(f, "\n");
//	fprintf(f, "Bias Weights:\n");
//	fprintf(f, "\n");
//	for (int j = 0; j < m_inputLayer.m_numChildNodes; j++)
//		fprintf(f, "(%d) = %f\n", j, m_inputLayer.m_biasWeights[j]);
//
//	fprintf(f, "\n");
//	fprintf(f, "\n");
//
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "Hidden Layer\n");
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "\n");
//	fprintf(f, "Weights:\n");
//	fprintf(f, "\n");
//	for (int i = 0; i < m_hiddenLayer.m_numNodes; i++)
//		for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
//			fprintf(f, "(%d, %d) = %f\n", i, j, m_hiddenLayer.m_weights[i][j]);
//	fprintf(f, "\n");
//	fprintf(f, "Bias Weights:\n");
//	fprintf(f, "\n");
//	for (int j = 0; j < m_hiddenLayer.m_numChildNodes; j++)
//		fprintf(f, "(%d) = %f\n", j, m_hiddenLayer.m_biasWeights[j]);
//
//	fprintf(f, "\n");
//	fprintf(f, "\n");
//
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "Output Layer\n");
//	fprintf(f, "--------------------------------------------------------\n");
//	fprintf(f, "\n");
//	fprintf(f, "Node Values:\n");
//	fprintf(f, "\n");
//	for (int i = 0; i < m_outputLayer.m_numNodes; i++)
//		fprintf(f, "(%d) = %f\n", i, m_outputLayer.m_neuronValues[i]);
//	fprintf(f, "\n");
//
//	fclose(f);
//}