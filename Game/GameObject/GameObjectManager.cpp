//======================================================
// File Name	: GameObjectManager.cpp
// Summary		: ゲームオブジェクトマネジャー
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObjectManager.h"

#include <Game/GameObject/GameObject.h>


/// <summary>
/// コンストラクタ
/// </summary>
GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
	, m_drawPrio()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameObjectManager::~GameObjectManager()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void GameObjectManager::Update(const DX::StepTimer& timer)
{
	DestroyObjects();

	if (!m_objectQueue.empty())
	{
		AcceptObjects();
	}

	UpdateObjects(timer);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void GameObjectManager::Render()
{
	std::list<GameObject*> pObjects;
	GameObjectList::iterator it = m_objects.begin();
	GameObjectList::iterator end = m_objects.end();
	while (it != end)
	{
		pObjects.push_back((*it).get());
		++it;
	}
	pObjects.sort([](const GameObject* a, const GameObject* b) 
	{
			return a->GetDrawPrio() > b->GetDrawPrio();
	});
	for (GameObject* object : pObjects)
	{
		object->Render();
	}
}

/// <summary>
/// 追加
/// </summary>
/// <param name="object">オブジェクト</param>
void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}

/// <summary>
/// 指定タグのみを取得
/// </summary>
/// <param name="tag">指定タグ</param>
/// <returns>オブジェクトのベクター</returns>
std::vector<GameObject*> GameObjectManager::Find(const GameObject::ObjectTag& tag)
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	return result;
}

/// <summary>
/// オブジェクト更新
/// </summary>
/// <param name="timer">タイマー</param>
void GameObjectManager::UpdateObjects(const DX::StepTimer& timer)
{
	for (GameObjectList::iterator itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		(*itr)->Update(timer);
	}
}

/// <summary>
/// 一番後ろに追加
/// </summary>
void GameObjectManager::AcceptObjects()
{
	// イテレータ
	GameObjectList::iterator it  = m_objectQueue.begin();
	GameObjectList::iterator end = m_objectQueue.end();
	while (it != end)
	{
		m_objects.push_back(std::move(*it));
		++it;
	}
	m_objectQueue.clear();

}

/// <summary>
/// オブジェクト消去
/// </summary>
void GameObjectManager::DestroyObjects()
{
	//  イテレータ
	GameObjectList::iterator it  = m_objects.begin();
	while (it != m_objects.end())
	{
		if ((*it)->IsInvalid())
		{
			it = m_objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}