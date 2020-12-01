//======================================================
// File Name	: RayCollider.cpp
// Summary		: ���C
// Author		: Kyoya Sakamoto
//======================================================
#include "RayCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">�o�^�����I�u�W�F�N�g</param>
/// <param name="size">��ӂ̔����̒���</param>
RayCollider::RayCollider(GameObject* owner)
	: Collider(owner)
	, m_posA()
	, m_posB()
{
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool RayCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool RayCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool RayCollider::IsCollided(const BoxCollider* collider) const
{
	return  CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool RayCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
