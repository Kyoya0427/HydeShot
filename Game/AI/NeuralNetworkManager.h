//======================================================
// File Name	: NeuralNetworkManager.h
// Summary		: �j���[�����l�b�g���[�N�Ń��[�h�I��
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/AI/Ai.h>

class NeuralNetwork;

class NeuralNetworkManager : public Ai
{
private:
	struct OutputData
	{
		float inputDis;
		float inputDegree;
		float inputHp;
		float inputShot;
		float outputDis;
		float outputDegree;
		float outputShot;
	};

public:
	//�R���X�g���N�^
	NeuralNetworkManager();
	//�f�X�g���N�^
	virtual ~NeuralNetworkManager();

public:
	static const int MAX_DATA_H = 301;
	static const int MAX_DATA_W = 7;
public:
	//�f�[�^���擾
	void InitializeTraining(wchar_t* fname);
	//�j���[�����l�b�g���[�N�̏�����
	void InitializeNeuralNetwork();
	//�s���p�^�[����I��
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys) override;
	void Render();

public:
	void OutputDataFile(char* fname);

public: 
	//�f�[�^���i�[
	std::vector<std::vector<float>> m_training;
	//�j���[�����l�b�g���[�N
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;

	float m_error;

	std::vector<OutputData>        m_outputData;
};

