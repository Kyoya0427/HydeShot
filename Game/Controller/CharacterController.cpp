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

/// <summary>
/// 攻撃にステイトを変更
/// </summary>
void CharacterController::ChangeAttackState()
{
	m_charaState = static_cast<CharaState*>(m_attack.get());
}

/// <summary>
/// サーチにステイトを変更
/// </summary>
void CharacterController::ChangeSearchState()
{
	m_charaState = static_cast<CharaState*>(m_search.get());
}

/// <summary>
/// 壁回避にステイトを変更
/// </summary>
void CharacterController::ChangeWallAvoidState()
{
	m_charaState = static_cast<CharaState*>(m_wallAvoid.get());
}
