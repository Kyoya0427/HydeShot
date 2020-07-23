//======================================================
// File Name	: CharacterController.cpp
// Summary		: �L�����N�^�[�R���g���[���[
// Date			: 2020/5/12
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
	m_attack    = std::make_unique<Attack>();
	m_search    = std::make_unique<Search>();
	m_wallAvoid = std::make_unique<WallAvoid>();

	m_attack->Initialize(m_character);
	m_search->Initialize(m_character);
	m_wallAvoid->Initialize(m_character);
	
	ChangeSearchState();
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
/// <returns></returns>
Character* CharacterController::GetCharacter()
{
	return m_character;
}

/// <summary>
/// �U���ɃX�e�C�g��ύX
/// </summary>
void CharacterController::ChangeAttackState()
{
	m_charaState = static_cast<CharaState*>(m_attack.get());
}

/// <summary>
/// �T�[�`�ɃX�e�C�g��ύX
/// </summary>
void CharacterController::ChangeSearchState()
{
	m_charaState = static_cast<CharaState*>(m_search.get());
}

/// <summary>
/// �ǉ���ɃX�e�C�g��ύX
/// </summary>
void CharacterController::ChangeWallAvoidState()
{
	m_charaState = static_cast<CharaState*>(m_wallAvoid.get());
}
