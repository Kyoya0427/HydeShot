//======================================================
// File Name	: ObjectManager.h
// Summary	: ゲーム画面と情報画面のオブジェクトマネージャーをまとめたクラス
//======================================================
#pragma once

class GameObjectManager;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

public:	// アクセッサ
		// ゲーム画面のオブジェクトマネージャー取得
	GameObjectManager* GetGameOM()
	{
		return m_gameOM.get();
	}
	// 情報画面のオブジェクトマネージャー取得
	GameObjectManager* GetInfoOM()
	{
		return m_infoOM.get();
	}

private:
	// ゲームオブジェクトマネージャー（ゲーム画面）
	std::unique_ptr<GameObjectManager>      m_gameOM;
	// ゲームオブジェクトマネージャー（情報画面）
	std::unique_ptr<GameObjectManager>      m_infoOM;
};

