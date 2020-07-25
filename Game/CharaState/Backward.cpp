//======================================================
// File Name	: Backward.h
// Summary		: ���ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Backward.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Backward::Backward()
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
/// <param name="controller">�R���g���[���[</param>
void Backward::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	m_controller = controller;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Backward::Update(const DX::StepTimer& timer)
{
	m_chara->Backward(AIController::MOVE_SPEED);
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
