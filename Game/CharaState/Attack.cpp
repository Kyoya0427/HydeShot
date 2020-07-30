//======================================================
// File Name	: Attack.h
// Summary		: �U���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

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
/// <param name="chara"></param>
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
	debugFont->print(10, 50, L"Attack");
	debugFont->draw();
}
