#pragma once

#include <list>
#include <memory>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>


class GameObject;



class GameObjectManager final
{
	using GameObjectPtr  = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;

	private:
		GameObjectList m_objects;
		GameObjectList m_objectQueue;
		int m_drawPrio;

	public:
		GameObjectManager();

	public:
		~GameObjectManager();

	public:
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer);
		void Add(GameObjectPtr&& object);

	private:
		void UpdateObjects(const DX::StepTimer& timer);
		void AcceptObjects();
		void DestroyObjects();
		const int GetDrawPrio() const;
		void SetDrawPrio(int prio);
};

inline const int GameObjectManager::GetDrawPrio() const
{
	return m_drawPrio;
}

inline void GameObjectManager::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}