//======================================================
// File Name	: CharacterController.cpp
// Summary		: �L�����N�^�[�R���g���[���[
// Author		: Kyoya  Sakamoto
//======================================================
#include "CharacterController.h"

#include <Game/GameObject/Character.h>

/// <summary>
/// �R���X�g���N
/// </summary>
CharacterController::CharacterController(Character* character)
	: m_character(character)
	, m_shotInterval()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterController::~CharacterController()
{
	m_character = nullptr;
}

/// <summary>
/// �L�������擾
/// </summary>
/// <returns>�L����</returns>
Character* CharacterController::GetCharacter()
{
	return m_character;
}


