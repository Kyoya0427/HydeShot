//======================================================
// File Name	: NeuralNetwork.h
// Summary		: �j���[�����l�b�g���[�N
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


	//���͂ƉB��w����m�[�h�̏d��
	//	std::vector<std::vector<double>>	m_weights;
	//	//�d�݂̒���
	//	std::vector<std::vector<double>>	m_weightChanges;
	//	//�v�Z���ʂ̒l
	//	std::vector<double>		m_neuronValues;
	//	//�^�[�Q�b�g�l���i�[
	//	std::vector<double>		m_desiredValues;
	//	//�G���[
	//	std::vector<double>		m_errors;
	//	//�o�C�A�X�̏d��
	//	std::vector<double>		m_biasWeights;

class NeuralNetworkLayer
{
public:
	//���͑w�m�[�h��
	int			                      m_numNodes;
	//�B��w�m�[�h��
	int			                      m_numChildNodes;
	//�o�͑w�m�[�h��
	int			                      m_numParentNodes;
	//���͂ƉB��w����m�[�h�̏d��
	std::vector<std::vector<double>>  m_weights;
	//�d�݂̒���
	std::vector<std::vector<double>>  m_weightChanges;
	//�v�Z���ʂ̒l
	std::vector<double>               m_neuronValues;
	//�^�[�Q�b�g�l���i�[
	std::vector<double>               m_desiredValues;
	//�G���[
	std::vector<double>               m_errors;
	//�o�C�A�X�̏d��
	std::vector<double>               m_biasWeights;
	//�o�C�A�X�l
	std::vector<double>               m_biasValues;
	//�d�݂̒������v�Z����w�K����ێ�
	double		                      m_learningRate;
	//���`�������֐��g�p�i�f�t�Hfalse�j
	bool		                      m_linearOutput;
	//���[�����^���g�p�i�f�t�Hfalse�j
	bool		                      m_useMomentum;
	//�O�q���[�����^��������ێ��i���[�����g�g�p���̂ݎg�p�j
	double		                      m_momentumFactor;
	//�e�w���i�[(���͑w�̏ꍇNULL)
	NeuralNetworkLayer*               m_parentLayer;
	//�q�w���i�[(�o�͑w�̏ꍇNULL)
	NeuralNetworkLayer*               m_childLayer;

public:
	//�R���X�g���N�^
	NeuralNetworkLayer();
	//������
	void Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
	//�������[���
	void CleanUp();
	// �w�K���J�n����Ƃ������Ă�
	void RandomizeWeights();
	// �G���[�����������ꂼ��ɑ��
	void CalculateErrors();
	// �d�݂𒲐�
	void AdjustWeights();
	// �S�Ă̏d�݂̌v�Z
	void CalculateNeuronValues();

};


class NeuralNetwork
{
public:
	//���͑w
	NeuralNetworkLayer	m_inputLayer;
	//�B��w
	NeuralNetworkLayer	m_hiddenLayer;
	//�o�͑w
	NeuralNetworkLayer	m_outputLayer;
	// ������
	void Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
	//�������[���
	void CleanUp();
	//���͂�ݒ�
	void SetInput(int i, double value);
	//�o�͒l
	double GetOutput(int i);
	//�]�܂����l��ݒ�
	void SetDesiredOutput(int i, double value);
	//�d�݂̌v�Z
	void FeedForward();
	//�o�͂ƉB��w�̃G���[�����Ƃɓ��͒l�ƉB��w�̏d�݂𒲐�
	void BackPropagate();
	//�o�͑w�̂����Ƃ��������̂𔻒f����
	int	GetMaxOutputID();
	//�o�͒l�Ɩ]�܂����l�̏W���Ɋ֌W����G���[
	double CalculateError();
	//�w�K����ݒ�
	void SetLearningRate(double rate);
	//���`�������֐����g�����ݒ�
	void SetLinearOutput(bool useLinear);

	void SetMomentum(bool useMomentum, double factor);
	//�f�[�^���o��
	void DumpData(char* filename);


};