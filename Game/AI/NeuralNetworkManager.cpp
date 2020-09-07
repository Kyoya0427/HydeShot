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
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetwork.h>

#include <Game/CharaState/CharaStateID.h>

#include <Game/GameObject/Character.h>

#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="enemy">�G�L�����N�^�[</param>
NeuralNetworkManager::NeuralNetworkManager(Character* character, Character* enemy)
	: m_isDirectionLeft()
	, m_isDirectionRight()
	, m_character(character)
	, m_enemy(enemy)
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources//CSV//test6.csv");
	InitializeNeuralNetwork();
	m_error = 0.0f;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
	OutputDataFile("Resources//CSV//OutputData.csv");
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

	m_training = std::vector<std::vector<float>>(MAX_DATA_H, std::vector<float>(MAX_DATA_W, 0));

	// �X�e�[�W�f�[�^�̓ǂݍ���
	for (int i = 0; i < MAX_DATA_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < MAX_DATA_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_training[i][j] = std::stof(tmp);
		}
	}
}

/// <summary>
/// �j���[�����l�b�g���[�N�̏�����
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// �j���[�����l�b�g���[�N������������(���͑w:6�A�B��w:20�A�o�͑w:5)
	m_neuralNetwork->Initialize(6, 20, 5);

	// �w�K����ݒ肷��
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	float	error = 1.0;
	int		count = 0;    
	// �덷�t�`�d����(Back propagate)
	while (error > 0.01 && count < 1000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			//���͒l
			//����
			m_neuralNetwork->SetInput(0, m_training[i][0]);			
			//������
			m_neuralNetwork->SetInput(1, m_training[i][1]);			
			//�E����
			m_neuralNetwork->SetInput(2, m_training[i][2]);			
			//��
			m_neuralNetwork->SetInput(3, m_training[i][3]);		
			//�ł�
			m_neuralNetwork->SetInput(4, m_training[i][4]);			
			
			//�o�͒l
			//����
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][5]);
			//������
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][6]);
			//�E����
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][7]);
			//��
			m_neuralNetwork->SetDesiredOutput(3, m_training[i][8]);
			//�ł�
			m_neuralNetwork->SetDesiredOutput(4, m_training[i][9]);

			//// �O���`�d����(Feed forward)
			m_neuralNetwork->FeedForward();
			//// �덷���v�Z����(Calculate error)
			error += m_neuralNetwork->CalculateError();
			//// �덷�t�`�d����(Back propagate)		
			m_neuralNetwork->BackPropagate();
		}
		error = error / MAX_DATA_H;
	}
	m_error = error;
	
}

/// <summary>
/// �s���p�^�[����I��
/// </summary>
/// <param name="character">���@</param>
/// <param name="enemys">�G</param>
/// <returns>�s���p�^�[��</returns>
CharaStateID NeuralNetworkManager::BehaviorSelection()
{
	//�����v�Z
	float distance = Vector3::Distance(m_character->GetPosition(), m_enemy->GetPosition());
	m_distance     = distance;
	//���E����
	SearchDirection(m_character, m_enemy);
	//����
	m_neuralNetwork->SetInput(0, distance / 16.0f);
	//������
	m_neuralNetwork->SetInput(1, static_cast<float>(m_isDirectionLeft));
	//�E����
	m_neuralNetwork->SetInput(2, static_cast<float>(m_isDirectionRight));
	//�ڂ̑O�ɕǂ�����
	m_neuralNetwork->SetInput(3, static_cast<float>(m_character->GetWallDiscovery()));
	//�G�����Ă邩����
	m_neuralNetwork->SetInput(4, static_cast<float>(m_character->GetEnemySightContact()));
	//�v�Z�J�n
	m_neuralNetwork->FeedForward();

	//�O���Ƀf�[�^�o�͂���ׂɕۊ�
	m_data = {};

	m_data.inputDis        = distance / 16.0f;
	m_data.inputLeft       = static_cast<float>(m_isDirectionLeft);
	m_data.inputRight      = static_cast<float>(m_isDirectionRight);
	m_data.inputWall       = static_cast<float>(m_character->GetWallDiscovery());
	m_data.inputShoot      = static_cast<float>(m_character->GetEnemySightContact());

	m_data.outputDis       = m_neuralNetwork->GetOutput(0);
	m_data.outputLeft      = m_neuralNetwork->GetOutput(1);
	m_data.outputRight     = m_neuralNetwork->GetOutput(2);
	m_data.outputWall      = m_neuralNetwork->GetOutput(3);
	m_data.outputShoot     = m_neuralNetwork->GetOutput(4);

	//�o�̓f�[�^����s����I��
	float dis   = m_neuralNetwork->GetOutput(0);
	float wall  = m_neuralNetwork->GetOutput(3);
	float shot  = m_neuralNetwork->GetOutput(4);

	if (shot >= 0.5f)
	{
		m_data.outputChoiceMode = "ATTACK";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"ATTACK");
		return	CharaStateID::ATTACK;
	}
	else if (wall >= 0.8)
	{
		m_data.outputChoiceMode = "WALLAVOID";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"WALLAVOID");
		return	CharaStateID::WALLAVOID;
	}
	else if (dis > 0.001f)
	{
		m_data.outputChoiceMode = "SEARCH";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"SEARCH");
		return CharaStateID::SEARCH;
	}

	m_data.outputChoiceMode = "none";
	m_outputData.push_back(m_data);
	return CharaStateID::NONE;
}

/// <summary>
/// ���E����
/// </summary>
/// <param name="character">���@</param>
/// <param name="enemy">�G</param>
void NeuralNetworkManager::SearchDirection(Character* character, Character* enemy)
{
	Vector3 u;
	//�t���O��������
	m_isDirectionLeft = false;
	m_isDirectionRight = false;

	//���E����v�Z
	Vector3 cv = Rotate(character->GetRadiansY(), Vector3::Forward);
	DirectX::SimpleMath::Vector3 rv = enemy->GetPosition() - character->GetPosition();
	rv.Normalize();
	DirectX::SimpleMath::Vector3 n = cv.Cross(rv);

	//�K�����t���Otrue
	if (n.y > 0.1f)
		m_isDirectionLeft = true;
	else if (n.y < -0.1f)
		m_isDirectionRight = true;
}

/// <summary>
/// ���όv�Z
/// </summary>
/// <param name="angle">���W�A��</param>
/// <param name="u">����</param>
/// <returns></returns>
Vector3 NeuralNetworkManager::Rotate(float angle, const Vector3& u)
{
	float	x, z;

	x = u.x * cos(angle) + u.z * sin(angle);
	z = -u.x * sin(angle) + u.z * cos(angle);

	return Vector3(x, 0, z);
}

/// <summary>
/// ���͂Əo�͂̒l���O���ɏo��
/// </summary>
/// <param name="fname">�o�͂��邽�߂̃t�@�C��</param>
void NeuralNetworkManager::OutputDataFile(char* fname)
{
	FILE* f;

	errno_t error;
	error = fopen_s(&f, fname, "w");

	fprintf(f, "-------------------------------------------------------------------------------------------------------\n");
	fprintf(f, "IN Distance, Left, Right, Wall, Shoot, Hp,  OUT Distance, Left, Right, Wall, Shoot ,ChoiceMode, Error  \n");
	fprintf(f, "-------------------------------------------------------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %s, %f%%  \n"
			,output.inputDis, output.inputLeft, output.inputRight, output.inputWall,output.inputShoot
			,output.outputDis, output.outputLeft, output.outputRight, output.outputWall, output.outputShoot
			,output.outputChoiceMode, m_error*100);
	}
	fclose(f);
}