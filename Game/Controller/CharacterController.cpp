//======================================================
// File Name	: CharacterController.cpp
// Summary		: キャラクターコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "CharacterController.h"

#include <Game/GameObject/Character.h>

/// <summary>
/// コンストラク
/// </summary>
CharacterController::CharacterController(Character* character)
	: m_character(character)
	, m_shotInterval(0.0f)
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
/// <returns></returns>
Character* CharacterController::GetCharacter()
{
	return m_character;
}
