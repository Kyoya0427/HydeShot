//======================================================
// File Name	: ObjectManager.cpp
// Summary	: ゲーム画面と情報画面のオブジェクトマネージャーをまとめたクラス
//======================================================
#include "ObjectManager.h"

#include <Game\GameObject\GameObjectManager.h>

ObjectManager::ObjectManager()
{
	// ゲーム画面用オブジェクトマネージャー生成
	m_gameOM = std::make_unique<GameObjectManager>();
	// 情報画面用オブジェクトマネージャー生成
	m_infoOM = std::make_unique<GameObjectManager>();
}


ObjectManager::~ObjectManager()
{
}
