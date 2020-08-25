//======================================================
// File Name	: Attack.cpp
// Summary		: �U���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Attack::Attack()
	: m_chara()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="enemy">�G�L�����N�^�[</param>
void Attack::Initialize(Character* chara, Character* enemy)
{
	enemy;
	m_chara = chara;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Attack::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Shoot();
}

/// <summary>
/// �`��
/// </summary>
void Attack::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, static_cast<Color>(Colors::White), 1.0f, L"Attack");
	debugFont->draw();
}
