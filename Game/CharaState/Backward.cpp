//======================================================
// File Name	: Backward.cpp
// Summary		: ���ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Backward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Backward::Backward()
	: m_chara()
	, m_enemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Backward::~Backward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void Backward::Initialize(Character* chara, Character* enemy)
{
	m_chara = chara;
	m_enemy = enemy;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Backward::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Backward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::BACKWARD_ANGLE);
}

/// <summary>
/// �`��
/// </summary>
void Backward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Backward");
	debugFont->draw();
}