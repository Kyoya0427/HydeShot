//======================================================
// File Name	: GameObjectManager.cpp
// Summary		: �Q�[���I�u�W�F�N�g�}�l�W���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObjectManager.h"

#include <Game/GameObject/GameObject.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
	,m_drawPrio(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObjectManager::~GameObjectManager()
{
}

/// <summary>
/// �X�V
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
/// �`��
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
	pObjects.sort([](const GameObject* a, const GameObject* b) {
		return a->GetDrawPrio() > b->GetDrawPrio();
	});
	for (GameObject* object : pObjects)
	{
		object->Render();
	}
}

/// <summary>
/// �ǉ�
/// </summary>
/// <param name="object"></param>
void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}

/// <summary>
/// �w��^�O�݂̂��擾
/// </summary>
/// <param name="tag">�w��^�O</param>
/// <returns></returns>
std::vector<GameObject*> GameObjectManager::Find(GameObject::ObjectTag tag)
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
/// �I�u�W�F�N�g�X�V
/// </summary>
/// <param name="timer"></param>
void GameObjectManager::UpdateObjects(const DX::StepTimer& timer)
{
	for (GameObjectList::iterator itr = m_objects.begin(); itr != m_objects.end(); itr++)
	{
		(*itr)->Update(timer);
	}
}

/// <summary>
/// ��Ԍ��ɒǉ�
/// </summary>
void GameObjectManager::AcceptObjects()
{
	// �C�e���[�^
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
/// �I�u�W�F�N�g����
/// </summary>
void GameObjectManager::DestroyObjects()
{
	//  �C�e���[�^
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
