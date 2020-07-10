//======================================================
// File Name	: NeuralNetworkManager.cpp
// Summary		: �j���[�����l�b�g���[�N�Ń��[�h�I��
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "NeuralNetworkManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include <Game/Common/DebugFont.h>

#include <Game/AI/NeuralNetwork.h>

#include <Game/GameObject/Character.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
NeuralNetworkManager::NeuralNetworkManager()
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources\\CSV\\TrainingSet.csv");
	InitializeNeuralNetwork();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
}

/// <summary>
/// �f�[�^���擾
/// </summary>
/// <param name="fname">�t�@�C���l�[��</param>
void NeuralNetworkManager::InitializeTraining(wchar_t* fname)
{
	std::wstring str;
	// �t�@�C���̃I�[�v��
	std::wifstream ifs(fname);

	m_training = std::vector<std::vector<double>>(MAX_DATA_H, std::vector<double>(MAX_DATA_W, 0));

	// �X�e�[�W�f�[�^�̓ǂݍ���
	for (int i = 0; i < MAX_DATA_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < MAX_DATA_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_training[i][j] = std::stoi(tmp);
		
		}
	}
}

/// <summary>
/// �j���[�����l�b�g���[�N�̏�����
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// �j���[�����l�b�g���[�N������������(���͑w:3�A�B��w:60�A�o�͑w:1)
	m_neuralNetwork->Initialize(3, 40, 1);

	// �w�K����ݒ肷��
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	double	error = 1.0;
	int		count = 0;
	// �덷�t�`�d����(Back propagate)
	while (error > 0.01 && count < 100)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			m_neuralNetwork->SetInput(0, m_training[i][0] / 13);			//X����
			m_neuralNetwork->SetInput(1, m_training[i][1] / 13);			//Y����
			m_neuralNetwork->SetInput(2, m_training[i][2] /  5);			//HP

			m_neuralNetwork->SetDesiredOutput(0, m_training[i][3] /7);	//�s���I��

			//// �O���`�d����(Feed forward)
			m_neuralNetwork->FeedForward();
			//// �덷���v�Z����(Calculate error)
			error += m_neuralNetwork->CalculateError();
			//// �덷�t�`�d����(Back propagate)		
			m_neuralNetwork->BackPropagate();
		}
		error = error / MAX_DATA_H;
	}
}

/// <summary>
/// �s���p�^�[����I��
/// </summary>
/// <param name="character">�L����</param>
/// <param name="enemys">�G</param>
/// <returns>�s���p�^�[��</returns>
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemys)
{
	Vector3 chara = character->GetPosition();
	Vector3 enemy = enemys->GetPosition();
	float x = chara.x - enemy.x;
	float z = chara.z - enemy.z;

	m_neuralNetwork->SetInput(0, x /13);
	m_neuralNetwork->SetInput(1, z /13);
	m_neuralNetwork->SetInput(2, character->GetHp() / 5);
	m_neuralNetwork->FeedForward();

	return static_cast<AIController::Behavior>(static_cast<int>(m_neuralNetwork->GetOutput(0) * 7));
}

