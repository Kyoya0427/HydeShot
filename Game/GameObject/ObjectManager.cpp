//======================================================
// File Name	: ObjectManager.cpp
// Summary	: �Q�[����ʂƏ���ʂ̃I�u�W�F�N�g�}�l�[�W���[���܂Ƃ߂��N���X
//======================================================
#include "ObjectManager.h"

#include <Game\GameObject\GameObjectManager.h>

ObjectManager::ObjectManager()
{
	// �Q�[����ʗp�I�u�W�F�N�g�}�l�[�W���[����
	m_gameOM = std::make_unique<IGameObjectManager>();
	// ����ʗp�I�u�W�F�N�g�}�l�[�W���[����
	m_infoOM = std::make_unique<IGameObjectManager>();
}


ObjectManager::~ObjectManager()
{
}
