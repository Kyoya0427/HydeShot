//======================================================
// File Name	: NeuralNetwork.h
// Summary		: �j���[�����l�b�g���[�N
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


class NeuralNetworkLayer
{
public:
	int			NumberOfNodes;
	int			NumberOfChildNodes;
	int			NumberOfParentNodes;
	float** Weights;
	float** WeightChanges;
	float* NeuronValues;
	float* DesiredValues;
	float* Errors;
	float* BiasWeights;
	float* BiasValues;
	float		LearningRate;

	bool		LinearOutput;
	bool		UseMomentum;
	float		MomentumFactor;

	NeuralNetworkLayer* ParentLayer;
	NeuralNetworkLayer* ChildLayer;

	NeuralNetworkLayer();

	void	Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
	void	CleanUp(void);
	void	RandomizeWeights(void);
	void	CalculateErrors(void);
	void	AdjustWeights(void);
	void	CalculateNeuronValues(void);

};

// Implements a 3-Layer neural network with one input layer, one hidden layer, and one output layer
class NeuralNetwork
{
public:
	NeuralNetworkLayer	InputLayer;
	NeuralNetworkLayer	HiddenLayer;
	NeuralNetworkLayer	OutputLayer;

	void	Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
	void	CleanUp();
	void	SetInput(int i, float value);
	float	GetOutput(int i);
	void	SetDesiredOutput(int i, float value);
	void	FeedForward(void);
	void	BackPropagate(void);
	int		GetMaxOutputID(void);
	float	CalculateError(void);
	void	SetLearningRate(float rate);
	void	SetLinearOutput(bool useLinear);
	void	SetMomentum(bool useMomentum, float factor);
	void	DumpData(char* filename);


};

//class NeuralNetwork
//{
//private:
//	class NeuralNetworkLayer
//	{
//		using DataType = float;
//		using DataArray = std::unique_ptr<DataType[]>;
//		using DataArray2d = std::unique_ptr<DataArray[]>;
//
//	public:
//		//���͑w�m�[�h��
//		int			                      m_numNodes;
//		//�B��w�m�[�h��
//		int			                      m_numChildNodes;
//		//�o�͑w�m�[�h��
//		int			                      m_numParentNodes;
//		//���͂ƉB��w����m�[�h�̏d��
//		DataArray2d  m_weights;
//		//�d�݂̒���
//		DataArray2d  m_weightChanges;
//		//�v�Z���ʂ̒l
//		DataArray               m_neuronValues;
//		//�^�[�Q�b�g�l���i�[
//		DataArray               m_desiredValues;
//		//�G���[
//		DataArray               m_errors;
//		//�o�C�A�X�̏d��
//		DataArray               m_biasWeights;
//		//�o�C�A�X�l
//		DataArray               m_biasValues;
//		//�d�݂̒������v�Z����w�K����ێ�
//		DataType		                      m_learningRate;
//		//���`�������֐��g�p�i�f�t�Hfalse�j
//		bool		                      m_linearOutput;
//		//���[�����^���g�p�i�f�t�Hfalse�j
//		bool		                      m_useMomentum;
//		//�O�q���[�����^��������ێ��i���[�����g�g�p���̂ݎg�p�j
//		DataType		                      m_momentumFactor;
//		//�e�w���i�[(���͑w�̏ꍇNULL)
//		NeuralNetworkLayer* m_parentLayer;
//		//�q�w���i�[(�o�͑w�̏ꍇNULL)
//		NeuralNetworkLayer* m_childLayer;
//
//	public:
//		//�R���X�g���N�^
//		NeuralNetworkLayer();
//		//������
//		void Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
//		//�������[���
//		void CleanUp();
//		// �w�K���J�n����Ƃ������Ă�
//		void RandomizeWeights();
//		// �G���[�����������ꂼ��ɑ��
//		void CalculateErrors();
//		// �d�݂𒲐�
//		void AdjustWeights();
//		// �S�Ă̏d�݂̌v�Z
//		void CalculateNeuronValues();
//
//	};
//public:
//	//���͑w
//	NeuralNetworkLayer	m_inputLayer;
//	//�B��w
//	NeuralNetworkLayer	m_hiddenLayer;
//	//�o�͑w
//	NeuralNetworkLayer	m_outputLayer;
//	// ������
//	void Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
//	//�������[���
//	void CleanUp();
//	//���͂�ݒ�
//	void SetInput(int i, float value);
//	//�o�͒l
//	float GetOutput(int i);
//	//�]�܂����l��ݒ�
//	void SetDesiredOutput(int i, float value);
//	//�d�݂̌v�Z
//	void FeedForward();
//	//�o�͂ƉB��w�̃G���[�����Ƃɓ��͒l�ƉB��w�̏d�݂𒲐�
//	void BackPropagate();
//	//�o�͑w�̂����Ƃ��������̂𔻒f����
//	int	GetMaxOutputID();
//	//�o�͒l�Ɩ]�܂����l�̏W���Ɋ֌W����G���[
//	float CalculateError();
//	//�w�K����ݒ�
//	void SetLearningRate(float rate);
//	//���`�������֐����g�����ݒ�
//	void SetLinearOutput(bool useLinear);
//	//���[�����g��ݒ�
//	void SetMomentum(bool useMomentum, float factor);
//	//�f�[�^���o��
//	void DumpData(char* filename);
//
//};