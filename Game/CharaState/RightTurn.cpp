//======================================================
// File Name	: RightTurn.h
// Summary		: �E��]�X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "RightTurn.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
RightTurn::RightTurn()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RightTurn::~RightTurn()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�R���g���[���[</param>
void RightTurn::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	m_controller = controller;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void RightTurn::Update(const DX::StepTimer& timer)
{
	m_chara->RightTurn(AIController::ROT_SPEED);

}

/// <summary>
/// �`��
/// </summary>
void RightTurn::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"RightTurn");
	debugFont->draw();
}
