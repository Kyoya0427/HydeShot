//======================================================
// File Name	: GameObjectManager.h
// Summary		: ゲームオブジェクトマネジャー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <list>
#include <memory>
#include <vector>

#include <DirectXTK/SimpleMath.h>

#include <Game/Common/StepTimer.h>

#include <Game/GameObject/GameObject.h>


class GameObjectManager final
{
//名前変更
using GameObjectPtr  = std::unique_ptr<GameObject>;
using GameObjectList = std::list<GameObjectPtr>;

public:
	//コンストラクタ
	GameObjectManager();

public:
	//デストラクタ
	~GameObjectManager();

public:
	//更新
	void Update(const DX::StepTimer& timer);
	//描画
	void Render();
	//追加
	void Add(GameObjectPtr&& object);
	//特定のオブジェクトを取得
	std::vector<GameObject*> Find(GameObject::ObjectTag tag);

private:
	//追加されたオブジェクトの更新
	void UpdateObjects(const DX::StepTimer& timer);
	//一番後ろに追加
	void AcceptObjects();
	//オブジェクト消去
	void DestroyObjects();
	//描画順登録
	const int GetDrawPrio() const;
	//描画順設定
	void SetDrawPrio(int prio);

private:
	GameObjectList m_objects;
	GameObjectList m_objectQueue;
	int m_drawPrio;
};


/// <summary>
/// 描画順登録
/// </summary>
/// <returns></returns>
inline const int GameObjectManager::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// 描画順設定
/// </summary>
/// <param name="prio"></param>
inline void GameObjectManager::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}