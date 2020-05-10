#pragma once

#include <list>
#include <memory>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>


class IGameObject;



class IGameObjectManager final
{
	using IGameObjectPtr  = std::unique_ptr<IGameObject>;
	using IGameObjectList = std::list<IGameObjectPtr>;

	private:
		IGameObjectList m_objects;
		IGameObjectList m_objectQueue;
		int m_drawPrio;


	public:
		IGameObjectManager();

	public:
		~IGameObjectManager();

	public:
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer);
		void Add(IGameObjectPtr&& object);

	private:
		void UpdateObjects(const DX::StepTimer& timer);
		void AcceptObjects();
		void DestroyObjects();
		const int GetDrawPrio() const;
		void SetDrawPrio(int prio);
};


inline const int IGameObjectManager::GetDrawPrio() const
{
	return m_drawPrio;
}

inline void IGameObjectManager::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}