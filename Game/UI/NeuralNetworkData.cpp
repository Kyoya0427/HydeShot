//======================================================
// File Name	: InfoWindow.h
// Summary		: ���E�B���h�E
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "NeuralNetworkData.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
NeuralNetworkData::NeuralNetworkData()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
NeuralNetworkData::~NeuralNetworkData()
{
}

/// <summary>
/// ������
/// </summary>
void NeuralNetworkData::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void NeuralNetworkData::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// �`��
/// </summary>
void NeuralNetworkData::Render()
{
	NeuralNetworkManager::OutputData data = GameContext::Get<NeuralNetworkManager>()->GetOutputData();
	DebugFont* debugFont = DebugFont::GetInstance();
	 
	debugFont->print(70, 20, static_cast<Color>(Colors::White), 1.3f, L" Input data", data.inputDis);
	debugFont->draw();

	debugFont->print(30, 60, static_cast<Color>(Colors::White), 1.0f, L" Distance = %.2f", data.inputDis);
	debugFont->draw();

	debugFont->print(30, 80, static_cast<Color>(Colors::White), 1.0f, L" Left        = %.2f", data.inputLeft);
	debugFont->draw();

	debugFont->print(30, 100, static_cast<Color>(Colors::White), 1.0f, L" Rigjt       = %.2f", data.inputRight);
	debugFont->draw();

	debugFont->print(30, 120, static_cast<Color>(Colors::White), 1.0f, L" Wall       = %.2f", data.inputWall);
	debugFont->draw();

	debugFont->print(30, 140, static_cast<Color>(Colors::White), 1.0f, L" Shoot     = %.2f", data.inputShoot);
	debugFont->draw();

	debugFont->print(70, 180, static_cast<Color>(Colors::White), 1.3f, L" Output data", data.inputDis);
	debugFont->draw();

	debugFont->print(30, 220, static_cast<Color>(Colors::White), 1.0f, L" Distance = %.2f", data.outputDis);
	debugFont->draw();

	debugFont->print(30, 240, static_cast<Color>(Colors::White), 1.0f, L" Left        = %.2f", data.outputLeft);
	debugFont->draw();

	debugFont->print(30, 260, static_cast<Color>(Colors::White), 1.0f, L" Rigjt       = %.2f", data.outputRight);
	debugFont->draw();

	debugFont->print(30, 280, static_cast<Color>(Colors::White), 1.0f, L" Wall       = %.2f", data.outputWall);
	debugFont->draw();

	debugFont->print(30, 300, static_cast<Color>(Colors::White), 1.0f, L" Shoot     = %.2f", data.outputShoot);
	debugFont->draw();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void NeuralNetworkData::OnCollision(GameObject* object)
{
}
