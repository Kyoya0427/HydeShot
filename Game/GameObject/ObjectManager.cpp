//======================================================
// File Name	: ObjectManager.cpp
// Summary	: ゲーム画面と情報画面のオブジェクトマネージャーをまとめたクラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "ObjectManager.h"

#include <Game\GameObject\GameObjectManager.h>

/// <summary>
/// コンストラクタ
/// </summary>
ObjectManager::ObjectManager()
{
	// ゲーム画面用オブジェクトマネージャー生成
	m_gameOM = std::make_unique<GameObjectManager>();
	// 情報画面用オブジェクトマネージャー生成
	m_infoOM = std::make_unique<GameObjectManager>();
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectManager::~ObjectManager()
{
}
