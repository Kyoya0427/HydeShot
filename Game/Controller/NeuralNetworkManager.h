//======================================================
// File Name	: NeuralNetworkManager.h
// Summary		: �j���[�����l�b�g���[�N�Ń��[�h�I��
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/Controller/AIController.h>

class NeuralNetwork;
class Character;

class NeuralNetworkManager
{
public:
	//�R���X�g���N�^
	NeuralNetworkManager();
	//�f�X�g���N�^
	~NeuralNetworkManager();

public:
	static const int MAX_DATA_H = 3920; 
	static const int MAX_DATA_W = 4; 

public:
	//�f�[�^���擾
	void InitializeTraining(wchar_t* fname);
	//�j���[�����l�b�g���[�N�̏�����
	void InitializeNeuralNetwork();
	//�s���p�^�[����I��
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys);

public: 
	//�f�[�^���i�[
	std::vector<std::vector<double>> m_training;
	//�j���[�����l�b�g���[�N
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
};

