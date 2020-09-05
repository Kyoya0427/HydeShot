//======================================================
// File Name	: InfoWindow.h
// Summary		: ���E�B���h�E
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "SelectStateUi.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectStateUi::SelectStateUi()
{
	m_selectMode  = L"NONE";
	m_selectState = L"NONE";
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectStateUi::~SelectStateUi()
{
}

/// <summary>
/// ������
/// </summary>
void SelectStateUi::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void SelectStateUi::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// �`��
/// </summary>
void SelectStateUi::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(10, 350, static_cast<Color>(Colors::White), 1.0f, L" Mode =");
	debugFont->draw();
	debugFont->print(130, 350, static_cast<Color>(Colors::White), 1.0f, m_selectMode);
	debugFont->draw();
	debugFont->print(10, 380, static_cast<Color>(Colors::White), 1.0f, L" State =");
	debugFont->draw();
	debugFont->print(130, 380, static_cast<Color>(Colors::White), 1.0f, m_selectState);
	debugFont->draw();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void SelectStateUi::OnCollision(GameObject* object)
{
}
