//======================================================
// File Name	: CharacterController.cpp
// Summary		: キャラクターコントローラー
// Author		: Kyoya  Sakamoto
//======================================================
#include "CharacterController.h"

#include <Game/GameObject/Character.h>

/// <summary>
/// コンストラク
/// </summary>
CharacterController::CharacterController(Character* character)
	: m_character(character)
	, m_shotInterval()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CharacterController::~CharacterController()
{
	m_character = nullptr;
}

/// <summary>
/// キャラを取得
/// </summary>
/// <returns>キャラ</returns>
Character* CharacterController::GetCharacter()
{
	return m_character;
}


