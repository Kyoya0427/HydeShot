//======================================================
// File Name	: Leftward.h
// Summary		: ���ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Leftward.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Leftward::Leftward()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Leftward::~Leftward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�R���g���[���[</param>
void Leftward::Initialize(Character* chara, CharacterController* controller)
{
	m_chara      = chara;
	m_controller = controller;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Leftward::Update(const DX::StepTimer& timer)
{
	m_chara->Leftward(AIController::MOVE_SPEED);
}

/// <summary>
/// �`��
/// </summary>
void Leftward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Leftward");
	debugFont->draw();
}
