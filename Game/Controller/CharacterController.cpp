//======================================================
// File Name	: CharacterController.cpp
// Summary		: �v���C���[�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "CharacterController.h"

#include <Game\GameObject\Character.h>

/// <summary>
/// �R���X�g���N
/// </summary>
CharacterController::CharacterController(Character* character)
	: m_character(character)
	, m_shotInterval(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterController::~CharacterController()
{
	m_character = nullptr;
}
