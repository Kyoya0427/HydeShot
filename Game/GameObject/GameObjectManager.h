//======================================================
// File Name	: GameObjectManager.h
// Summary		: �Q�[���I�u�W�F�N�g�}�l�W���[
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
//���O�ύX
using GameObjectPtr  = std::unique_ptr<GameObject>;
using GameObjectList = std::list<GameObjectPtr>;

public:
	//�R���X�g���N�^
	GameObjectManager();

public:
	//�f�X�g���N�^
	~GameObjectManager();

public:
	//�X�V
	void Update(const DX::StepTimer& timer);
	//�`��
	void Render();
	//�ǉ�
	void Add(GameObjectPtr&& object);
	//����̃I�u�W�F�N�g���擾
	std::vector<GameObject*> Find(GameObject::ObjectTag tag);

private:
	//�ǉ����ꂽ�I�u�W�F�N�g�̍X�V
	void UpdateObjects(const DX::StepTimer& timer);
	//��Ԍ��ɒǉ�
	void AcceptObjects();
	//�I�u�W�F�N�g����
	void DestroyObjects();
	//�`�揇�o�^
	const int GetDrawPrio() const;
	//�`�揇�ݒ�
	void SetDrawPrio(int prio);

private:
	GameObjectList m_objects;
	GameObjectList m_objectQueue;
	int m_drawPrio;
};


/// <summary>
/// �`�揇�o�^
/// </summary>
/// <returns></returns>
inline const int GameObjectManager::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// �`�揇�ݒ�
/// </summary>
/// <param name="prio"></param>
inline void GameObjectManager::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}