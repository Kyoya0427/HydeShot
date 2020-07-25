//======================================================
// File Name	: LeftTurn.h
// Summary		: ����]�X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "LeftTurn.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
LeftTurn::LeftTurn()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LeftTurn::~LeftTurn()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�R���g���[���[</param>
void LeftTurn::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	m_controller = controller;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void LeftTurn::Update(const DX::StepTimer& timer)
{
	m_chara->LeftTurn(AIController::ROT_SPEED);
}

/// <summary>
/// �`��
/// </summary>
void LeftTurn::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"LeftTurn");
	debugFont->draw();
}
