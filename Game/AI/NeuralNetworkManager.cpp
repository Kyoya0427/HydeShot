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
	InitializeTraining(L"Resources\\CSV\\test.csv");
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
			m_training[i][j] = std::stod(tmp);
		
		}
	}
}

/// <summary>
/// �j���[�����l�b�g���[�N�̏�����
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// �j���[�����l�b�g���[�N������������(���͑w:3�A�B��w:60�A�o�͑w:1)
	m_neuralNetwork->Initialize(4, 20, 3);

	// �w�K����ݒ肷��
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// �������^����ݒ肷��
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	float	error = 1.0;
	int		count = 0;
	// �덷�t�`�d����(Back propagate)
	while (error > 0.1 && count < 1000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			//����
			m_neuralNetwork->SetInput(0, m_training[i][0]);			
			//�p�x
			m_neuralNetwork->SetInput(1, m_training[i][1]);			
			//HP
			m_neuralNetwork->SetInput(2, m_training[i][2]);			
			//��
			m_neuralNetwork->SetInput(3, m_training[i][3]);			
			
			//����
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][4]);
			//�p�x
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][5]);
			//���C
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][6]);

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
/// <param name="character">�L����</param>
/// <param name="enemys">�G</param>
/// <returns>�s���p�^�[��</returns>
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemys)
{
	float distance = Vector3::Distance(character->GetPosition(), enemys->GetPosition());
	OutputData data;
	////����
	//m_neuralNetwork->SetInput(0, 0);
	////�p�x
	//m_neuralNetwork->SetInput(1,0);
	////HP
	//m_neuralNetwork->SetInput(2, 1);
	////�ǔ���
	//m_neuralNetwork->SetInput(3, 1);

	//����
	m_neuralNetwork->SetInput(0, distance / 18.0f);
	//�p�x
	m_neuralNetwork->SetInput(1,enemys->GetDegreeY() / 360.0f);
	//HP
	m_neuralNetwork->SetInput(2, character->GetHp() / 5);
	//�G�����Ă邩����
	m_neuralNetwork->SetInput(3, character->GetEnemySightContact());

	data.inputDis    = distance / 18.0f;
	data.inputDegree = enemys->GetDegreeY() / 360.0f;
	data.inputHp     = character->GetHp() / 5;
	data.inputShot   = character->GetEnemySightContact();

	m_neuralNetwork->FeedForward();

	float dis  = m_neuralNetwork->GetOutput(0) * 18.0f;
	float rot  = m_neuralNetwork->GetOutput(1) * 360;
	float shot = m_neuralNetwork->GetOutput(2);

	data.outputDis    = dis;
	data.outputDegree = rot;
	data.outputShot   = shot;

	m_outputData.push_back(data);

	if(dis >= 10.0f)
		return	AIController::Behavior::MOVE_FORWARD;
	if (dis <= 6.0f)
		return AIController::Behavior::MOVE_BACKWARD;

	return AIController::Behavior::NONE;
}

void NeuralNetworkManager::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 100, L"dis = %f", m_neuralNetwork->GetOutput(0) * 18.0f);
	debugFont->draw();
	debugFont->print(10, 130, L"rot = %f", m_neuralNetwork->GetOutput(1) * 360.0f);
	debugFont->draw();
	debugFont->print(10, 160, L"s = %f", m_neuralNetwork->GetOutput(2));
	debugFont->draw();

	debugFont->print(10, 190, L"error = %f", m_error * 100.0f);
	debugFont->draw();
}

void NeuralNetworkManager::OutputDataFile(char* fname)
{
	FILE* f;

	errno_t error;
	error = fopen_s(&f, fname, "w");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "A = D, B = R, C = H, D = W, E = D, F = R, G = S \n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f,\n",output.inputDis,
			output.inputDegree,output.inputHp,output.inputShot,
			output.outputDis,output.outputDegree,output.outputShot );
	}
	fclose(f);
}



