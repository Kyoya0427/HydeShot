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
	: m_isDirectionLeft()
	, m_isDirectionRight()
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources\\CSV\\test5.csv");
	InitializeNeuralNetwork();
	m_error = 0.0f;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
	OutputDataFile("Resources\\CSV\\OutputData.csv");
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
	// �j���[�����l�b�g���[�N������������(���͑w:5�A�B��w:40�A�o�͑w:4)
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
	while (error > 0.01 && count < 10000)
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
			//HP
			m_neuralNetwork->SetInput(5, m_training[i][5]);

			//�o�͒l
			//����
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][6]);
			//������
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][7]);
			//�E����
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][8]);
			//��
			m_neuralNetwork->SetDesiredOutput(3, m_training[i][9]);
			//�ł�
			m_neuralNetwork->SetDesiredOutput(4, m_training[i][10]);

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
AIController::State NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemy)
{
	m_character = character;
	//�����v�Z
	float distance = Vector3::Distance(character->GetPosition(), enemy->GetPosition());
	m_distance = distance;
	//���E����
	SearchDirection(character, enemy);
	//����
	m_neuralNetwork->SetInput(0, distance / 18.0f);
	//������
	m_neuralNetwork->SetInput(1, static_cast<float>(m_isDirectionLeft));
	//�E����
	m_neuralNetwork->SetInput(2, static_cast<float>(m_isDirectionRight));
	//�ڂ̑O�ɕǂ�����
	m_neuralNetwork->SetInput(3, static_cast<float>(character->GetWallContact()));
	//�G�����Ă邩����
	m_neuralNetwork->SetInput(4, static_cast<float>(character->GetEnemySightContact()));
	//HP
	m_neuralNetwork->SetInput(5, static_cast<float>(character->GetHp() / 5));


	//�v�Z�J�n
	m_neuralNetwork->FeedForward();

	//�O���Ƀf�[�^�o�͂���ׂɕۊ�
	m_data = OutputData();

	m_data.inputDis      = distance / 18.0f;
	m_data.inputLeft     = static_cast<float>(m_isDirectionLeft);
	m_data.inputRight    = static_cast<float>(m_isDirectionRight);
	m_data.inputWall     = static_cast<float>(character->GetWallContact());
	m_data.inputShoot    = static_cast<float>(character->GetEnemySightContact());
	m_data.inputHp       = static_cast<float>(character->GetHp() / 5);

	m_data.outputDis       = m_neuralNetwork->GetOutput(0);
	m_data.outputLeft      = m_neuralNetwork->GetOutput(1);
	m_data.outputRight     = m_neuralNetwork->GetOutput(2);
	m_data.outputWall      = m_neuralNetwork->GetOutput(3);
	m_data.outputShoot     = m_neuralNetwork->GetOutput(4);

	
	float dis   = m_neuralNetwork->GetOutput(0);
	float left  = m_neuralNetwork->GetOutput(1);
	float right = m_neuralNetwork->GetOutput(2);
	float wall  = m_neuralNetwork->GetOutput(3);
	float shot  = m_neuralNetwork->GetOutput(4);

	if (shot >= 0.6f)
	{
		m_data.outputChoiceMode = "ATTACK";
		m_outputData.push_back(m_data);
		return	AIController::State::ATTACK;
	}
	else if (wall >= 0.6)
	{
		m_data.outputChoiceMode = "WALLAVOID";
		m_outputData.push_back(m_data);
		return	AIController::State::WALLAVOID;
	}
	else 
	{
		m_data.outputChoiceMode = "SEARCH";
		m_outputData.push_back(m_data);
		return AIController::State::SEARCH;
	}
	m_data.outputChoiceMode = "none";
	m_outputData.push_back(m_data);
	return AIController::State::NONE;
}

void NeuralNetworkManager::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(10, 190, L"error = %f%", m_error * 100);
	debugFont->draw();

	debugFont->print(700, 250, L"dis = %f", m_distance / 18.0f);
	debugFont->draw();

	if (m_isDirectionLeft)
	{
		debugFont->print(700, 280, L"left = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(700, 280, L"left = false");
		debugFont->draw();
	}

	if (m_isDirectionRight)
	{
		debugFont->print(700, 310, L"right = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(700, 310, L"right = false");
		debugFont->draw();
	}

	if (m_character->GetEnemySightContact())
	{
		debugFont->print(700, 340, L"shoot = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(700, 340, L"shoot = false");
		debugFont->draw();
	}
}

/// <summary>
/// ���E����
/// </summary>
/// <param name="character"></param>
/// <param name="enemy"></param>
void NeuralNetworkManager::SearchDirection(Character* character, Character* enemy)
{
	Vector3 u;
	m_isDirectionLeft = false;
	m_isDirectionRight = false;

	DirectX::SimpleMath::Vector3 cv = Rotate(character->GetRadiansY(), DirectX::SimpleMath::Vector3::Forward);
	DirectX::SimpleMath::Vector3 rv = enemy->GetPosition() - character->GetPosition();
	rv.Normalize();
	DirectX::SimpleMath::Vector3 n = cv.Cross(rv);

	if (n.y > 0.1f)
		m_isDirectionLeft = true;
	else if (n.y < -0.1f)
		m_isDirectionRight = true;
}

/// <summary>
/// 
/// </summary>
/// <param name="angle"></param>
/// <param name="u"></param>
/// <returns></returns>
Vector3 NeuralNetworkManager::Rotate(float angle, Vector3 u)
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
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %s, %f% \n"
			,output.inputDis, output.inputLeft, output.inputRight, output.inputWall,output.inputShoot, output.inputHp
			,output.outputDis, output.outputLeft, output.outputRight, output.outputWall, output.outputShoot
			,output.outputChoiceMode, m_error*100);
	}
	fclose(f);
}



