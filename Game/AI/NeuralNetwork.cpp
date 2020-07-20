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
NeuralNetworkLayer::NeuralNetworkLayer()
{
	ParentLayer = NULL;
	ChildLayer = NULL;
	LinearOutput = false;
	UseMomentum = false;
	MomentumFactor = 0.9;
}

void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{

	// Allocate memory
	NeuronValues = (float*)malloc(sizeof(float) * NumberOfNodes);
	DesiredValues = (float*)malloc(sizeof(float) * NumberOfNodes);
	Errors = (float*)malloc(sizeof(float) * NumberOfNodes);

	if (parent != NULL) {
		ParentLayer = parent;
	}

	if (child != NULL) {
		ChildLayer = child;

		Weights = (float**)malloc(sizeof(float*) * NumberOfNodes);
		WeightChanges = (float**)malloc(sizeof(float*) * NumberOfNodes);
		for (int i = 0; i < NumberOfNodes; i++) {
			Weights[i] = (float*)malloc(sizeof(float) * NumberOfChildNodes);
			WeightChanges[i] = (float*)malloc(sizeof(float) * NumberOfChildNodes);
		}

		BiasValues = (float*)malloc(sizeof(float) * NumberOfChildNodes);
		BiasWeights = (float*)malloc(sizeof(float) * NumberOfChildNodes);
	}
	else {
		Weights = NULL;
		BiasValues = NULL;
		BiasWeights = NULL;
	}

	// Make sure everything contains zeros
	for (int i = 0; i < NumberOfNodes; i++) {
		NeuronValues[i] = 0;
		DesiredValues[i] = 0;
		Errors[i] = 0;

		if (ChildLayer != NULL) {
			for (int j = 0; j < NumberOfChildNodes; j++) {
				Weights[i][j] = 0;
				WeightChanges[i][j] = 0;
			}
		}
	}

	if (ChildLayer != NULL) {
		for (int j = 0; j < NumberOfChildNodes; j++) {
			BiasValues[j] = -1;
			BiasWeights[j] = 0;
		}
	}
}

void NeuralNetworkLayer::CleanUp(void)
{
	int	i;

	free(NeuronValues);
	free(DesiredValues);
	free(Errors);

	if (Weights != NULL) {
		for (i = 0; i < NumberOfNodes; i++) {
			free(Weights[i]);
			free(WeightChanges[i]);
		}
		free(Weights);
		free(WeightChanges);
	}

	if (BiasValues != NULL)
		free(BiasValues);
	if (BiasWeights != NULL)
		free(BiasWeights);
}

void NeuralNetworkLayer::RandomizeWeights(void)
{
	int	min = 0;
	int	max = 200;
	int	number;

	srand((unsigned)time(NULL));

	for (int i = 0; i < NumberOfNodes; i++) {
		for (int j = 0; j < NumberOfChildNodes; j++) {
			number = (((abs(rand()) % (max - min + 1)) + min));
			if (number > max)
				number = max;
			if (number < min)
				number = min;
			Weights[i][j] = number / 100.0f - 1;
		}
	}

	for (int j = 0; j < NumberOfChildNodes; j++) {
		number = (((abs(rand()) % (max - min + 1)) + min));
		if (number > max)
			number = max;
		if (number < min)
			number = min;
		BiasWeights[j] = number / 100.0f - 1;
	}
}

void NeuralNetworkLayer::CalculateErrors(void)
{
	float	sum = 0.0;
	// 出力層(output layer)
	if (ChildLayer == NULL) {
		for (int i = 0; i < NumberOfNodes; i++) {
			Errors[i] = (DesiredValues[i] - NeuronValues[i]) * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	} // 入力層(input layer)
	else if (ParentLayer == NULL) {
		for (int i = 0; i < NumberOfNodes; i++) {
			Errors[i] = 0.0f;
		}
	} // 隠れ層(hidden layer)
	else {
		for (int i = 0; i < NumberOfNodes; i++) {
			sum = 0;
			for (int j = 0; j < NumberOfChildNodes; j++) {
				sum += ChildLayer->Errors[j] * Weights[i][j];
			}
			Errors[i] = sum * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	}
}

void NeuralNetworkLayer::AdjustWeights(void)
{
	float	dw = 0.0;
	if (ChildLayer != NULL) {
		for (int i = 0; i < NumberOfNodes; i++)
		{
			for (int j = 0; j < NumberOfChildNodes; j++)
			{
				dw = LearningRate * ChildLayer->Errors[j] * NeuronValues[i];
				Weights[i][j] += dw + MomentumFactor * WeightChanges[i][j];
				WeightChanges[i][j] = dw;
			}
		}

		for (int j = 0; j < NumberOfChildNodes; j++) {
			BiasWeights[j] += LearningRate * ChildLayer->Errors[j] * BiasValues[j];
		}
	}
}

void NeuralNetworkLayer::CalculateNeuronValues(void)
{
	float	x;
	if (ParentLayer != NULL)
	{
		for (int j = 0; j < NumberOfNodes; j++)
		{
			x = 0;
			for (int i = 0; i < NumberOfParentNodes; i++)
			{
				x += ParentLayer->NeuronValues[i] * ParentLayer->Weights[i][j];
			}
			x += ParentLayer->BiasValues[j] * ParentLayer->BiasWeights[j];

			if ((ChildLayer == NULL) && LinearOutput)
				NeuronValues[j] = x;
			else
				NeuronValues[j] = 1.0f / (1.0f + exp(-x));
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetwork Class
/////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
{
	InputLayer.NumberOfNodes = nNodesInput;
	InputLayer.NumberOfChildNodes = nNodesHidden;
	InputLayer.NumberOfParentNodes = 0;
	InputLayer.Initialize(nNodesInput, NULL, &HiddenLayer);
	InputLayer.RandomizeWeights();

	HiddenLayer.NumberOfNodes = nNodesHidden;
	HiddenLayer.NumberOfChildNodes = nNodesOutput;
	HiddenLayer.NumberOfParentNodes = nNodesInput;
	HiddenLayer.Initialize(nNodesHidden, &InputLayer, &OutputLayer);
	HiddenLayer.RandomizeWeights();

	OutputLayer.NumberOfNodes = nNodesOutput;
	OutputLayer.NumberOfChildNodes = 0;
	OutputLayer.NumberOfParentNodes = nNodesHidden;
	OutputLayer.Initialize(nNodesOutput, &HiddenLayer, NULL);
}

void NeuralNetwork::CleanUp()
{
	InputLayer.CleanUp();
	HiddenLayer.CleanUp();
	OutputLayer.CleanUp();
}

void	NeuralNetwork::SetInput(int i, float value)
{
	if ((i >= 0) && (i < InputLayer.NumberOfNodes)) {
		InputLayer.NeuronValues[i] = value;
	}
}

float	NeuralNetwork::GetOutput(int i)
{
	if ((i >= 0) && (i < OutputLayer.NumberOfNodes)) {
		return OutputLayer.NeuronValues[i];
	}
	return (float)INT_MAX; // to indicate an error
}

void NeuralNetwork::SetDesiredOutput(int i, float value)
{
	if ((i >= 0) && (i < OutputLayer.NumberOfNodes)) {
		OutputLayer.DesiredValues[i] = value;
	}
}

void NeuralNetwork::FeedForward(void)
{
	InputLayer.CalculateNeuronValues();
	HiddenLayer.CalculateNeuronValues();
	OutputLayer.CalculateNeuronValues();
}

void NeuralNetwork::BackPropagate(void)
{
	OutputLayer.CalculateErrors();
	HiddenLayer.CalculateErrors();

	HiddenLayer.AdjustWeights();
	InputLayer.AdjustWeights();
}

int	NeuralNetwork::GetMaxOutputID(void)
{
	float maxval = OutputLayer.NeuronValues[0];
	int id = 0;

	for (int i = 1; i < OutputLayer.NumberOfNodes; i++) {
		if (OutputLayer.NeuronValues[i] > maxval) {
			maxval = OutputLayer.NeuronValues[i];
			id = i;
		}
	}
	return id;
}

float NeuralNetwork::CalculateError(void)
{
	float	error = 0.0;

	for (int i = 0; i < OutputLayer.NumberOfNodes; i++) {
		error += pow(OutputLayer.NeuronValues[i] - OutputLayer.DesiredValues[i], 2);
	}
	error = error / OutputLayer.NumberOfNodes;
	return error;
}

void NeuralNetwork::SetLearningRate(float rate)
{
	InputLayer.LearningRate = rate;
	HiddenLayer.LearningRate = rate;
	OutputLayer.LearningRate = rate;
}

void NeuralNetwork::SetLinearOutput(bool useLinear)
{
	InputLayer.LinearOutput = useLinear;
	HiddenLayer.LinearOutput = useLinear;
	OutputLayer.LinearOutput = useLinear;
}

void NeuralNetwork::SetMomentum(bool useMomentum, float factor)
{
	InputLayer.UseMomentum = useMomentum;
	HiddenLayer.UseMomentum = useMomentum;
	OutputLayer.UseMomentum = useMomentum;

	InputLayer.MomentumFactor = factor;
	HiddenLayer.MomentumFactor = factor;
	OutputLayer.MomentumFactor = factor;
}

void NeuralNetwork::DumpData(char* filename)
{
	FILE* f;

	f = fopen(filename, "w");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Input Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for (int i = 0; i < InputLayer.NumberOfNodes; i++)
		fprintf(f, "(%d) = %f\n", i, InputLayer.NeuronValues[i]);
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for (int i = 0; i < InputLayer.NumberOfNodes; i++)
		for (int j = 0; j < InputLayer.NumberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, InputLayer.Weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for (int j = 0; j < InputLayer.NumberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, InputLayer.BiasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Hidden Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for (int i = 0; i < HiddenLayer.NumberOfNodes; i++)
		for (int j = 0; j < HiddenLayer.NumberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, HiddenLayer.Weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for (int j = 0; j < HiddenLayer.NumberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, HiddenLayer.BiasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Output Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for (int i = 0; i < OutputLayer.NumberOfNodes; i++)
		fprintf(f, "(%d) = %f\n", i, OutputLayer.NeuronValues[i]);
	fprintf(f, "\n");

	fclose(f);
}

///// <summary>
///// コンストラクタ
///// </summary>
//NeuralNetwork::NeuralNetworkLayer::NeuralNetworkLayer()
//{
//	m_parentLayer    = nullptr;
//	m_childLayer     = nullptr;
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
//	if (parent != nullptr)
//	{
//		m_parentLayer = parent;
//	}
//
//	if (child != nullptr)
//	{
//		m_childLayer    = child;
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
//		m_weights     = nullptr;
//		m_biasValues  = nullptr;
//		m_biasWeights = nullptr;
//	}
//
//	// Make sure everything contains zeros
//	for (int i = 0; i < m_numNodes; i++)
//	{
//		m_neuronValues[i]  = 0;
//		m_desiredValues[i] = 0;
//		m_errors[i]        = 0;
//
//		if (m_childLayer != nullptr)
//		{
//			for (int j = 0; j < m_numChildNodes; j++)
//			{
//				m_weights[i][j]       = 0;
//				m_weightChanges[i][j] = 0;
//			}
//		}
//	}
//
//	if (m_childLayer != nullptr)
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
//	srand((unsigned)time(nullptr));
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
//	if (m_childLayer == nullptr)
//	{
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			errors[i] = (desiredValues[i] - neuronValues[i]) * neuronValues[i] * (1.0f - desiredValues[i]);
//		}
//	}
//	// 入力層(input layer)
//	else if (m_parentLayer == nullptr)
//	{
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			errors[i] = 0.0f;
//		}
//	}
//	// 隠れ層(hidden layer)
//	else {
//		DataType* weights = nullptr;
//		DataType* childLayerErrors = &(m_childLayer->m_errors[0]);
//
//		for (int i = 0; i < m_numNodes; i++)
//		{
//			sum = 0;
//			weights = &m_weights[i][0];
//			for (int j = 0; j < m_numChildNodes; j++)
//			{
//				sum += childLayerErrors[j] * weights[j];
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
//	if (m_childLayer != nullptr)
//	{
//		for (int i = 0; i < m_numNodes; i++) 
//		{
//			weights = &m_weights[i][0];
//			weightChanges = &m_weightChanges[i][0];
//
//			for (int j = 0; j < m_numChildNodes; j++) 
//			{
//				dw               = m_learningRate * m_childLayer->m_errors[j] * neuronValues[i];
//				weights[j]      += dw + m_momentumFactor * weightChanges[j];
//				weightChanges[j] = dw;
//			}
//		}
//
//		DataType* childLayerErrors = &(m_childLayer->m_errors[0]);
//
//		for (int j = 0; j < m_numChildNodes; j++) 
//		{
//			biasWeights[j] += m_learningRate * childLayerErrors[j] * biasValues[j];
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
//	if (m_parentLayer != nullptr)
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
//			if ((m_childLayer == nullptr) && m_linearOutput)
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
//	m_inputLayer.Initialize(nNodesInput, nullptr, &m_hiddenLayer);
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
//	m_outputLayer.Initialize(nNodesOutput, &m_hiddenLayer, nullptr);
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