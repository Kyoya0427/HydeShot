//======================================================
// File Name	: ObjectManager.cpp
// Summary	: �Q�[����ʂƏ���ʂ̃I�u�W�F�N�g�}�l�[�W���[���܂Ƃ߂��N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "ObjectManager.h"

#include <Game\GameObject\GameObjectManager.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectManager::ObjectManager()
{
	// �Q�[����ʗp�I�u�W�F�N�g�}�l�[�W���[����
	m_gameOM = std::make_unique<GameObjectManager>();
	// ����ʗp�I�u�W�F�N�g�}�l�[�W���[����
	m_infoOM = std::make_unique<GameObjectManager>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectManager::~ObjectManager()
{
}
