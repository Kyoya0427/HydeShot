//======================================================
// File Name	: NeuralNetwork.h
// Summary		: �j���[�����l�b�g���[�N
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


class NeuralNetworkLayer
{
public:
	//���͑w�m�[�h��
	int			        m_numNodes;
	//�B��w�m�[�h��
	int			        m_numChildNodes;
	//�o�͑w�m�[�h��
	int			        m_numParentNodes;
	//���͂ƉB��w����m�[�h�̏d��
	float**             m_weights;
	//�d�݂̒���
	float**             m_weightChanges;
	//�v�Z���ʂ̒l
	float*              m_neuronValues;
	//�^�[�Q�b�g�l���i�[
	float*              m_desiredValues;
	//�G���[
	float*              m_errors;
	//�o�C�A�X�̏d��
	float*              m_biasWeights;
	//�o�C�A�X�l
	float*              m_biasValues;
	//�d�݂̒������v�Z����w�K����ێ�
	float		        m_learningRate;
	//���`�������֐��g�p�i�f�t�Hfalse�j
	bool		        m_linearOutput;
	//���[�����^���g�p�i�f�t�Hfalse�j
	bool		        m_useMomentum;
	//�O�q���[�����^��������ێ��i���[�����g�g�p���̂ݎg�p�j
	float		        m_momentumFactor;
	//�e�w���i�[(���͑w�̏ꍇNULL)
	NeuralNetworkLayer* m_parentLayer;
	//�q�w���i�[(�o�͑w�̏ꍇNULL)
	NeuralNetworkLayer* m_childLayer;

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

public:
	// ������
	void Initialize(int nodesInput, int nodesHidden, int nodesOutput);
	//�������[���
	void CleanUp();
	//���͂�ݒ�
	void SetInput(int i, float value);
	//�o�͒l
	float GetOutput(int i);
	//�]�܂����l��ݒ�
	void SetDesiredOutput(int i, float value);
	//�d�݂̌v�Z
	void FeedForward();
	//�o�͂ƉB��w�̃G���[�����Ƃɓ��͒l�ƉB��w�̏d�݂𒲐�
	void BackPropagate();
	//�o�͑w�̂����Ƃ��������̂𔻒f����
	int  GetMaxOutputID();
	//�o�͒l�Ɩ]�܂����l�̏W���Ɋ֌W����G���[
	float CalculateError();
	//�w�K����ݒ�
	void SetLearningRate(float rate);
	//���`�������֐����g�����ݒ�
	void SetLinearOutput(bool linear);
	//���[�����g��ݒ�
	void SetMomentum(bool momentum, float factor);
	//�f�[�^���o��
	void DumpData(char* filename);
	//�w�K�f�[�^�����
	void LearningDataInput(char* filename);

};