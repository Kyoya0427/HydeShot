//======================================================
// File Name	: HpUi.cpp
// Summary		: �j���[�����l�b�g���[�N�̏��
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "HpUi.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
HpUi::HpUi()
	: m_playerHp()
	, m_enemyHp()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HpUi::~HpUi()
{
}

/// <summary>
/// ������
/// </summary>
void HpUi::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void HpUi::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void HpUi::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(30, 500, static_cast<Color>(Colors::White), 1.3f, L"Player = %d", m_playerHp);
	debugFont->draw();

	debugFont->print(30, 530, static_cast<Color>(Colors::White), 1.3f, L"Enemy = %d", m_enemyHp);
	debugFont->draw();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void HpUi::OnCollision(GameObject* object)
{
	object;
}