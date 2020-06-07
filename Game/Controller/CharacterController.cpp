//======================================================
// File Name	: CharacterController.cpp
// Summary		: プレイヤークラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "CharacterController.h"

#include <Game\GameObject\Character.h>

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
