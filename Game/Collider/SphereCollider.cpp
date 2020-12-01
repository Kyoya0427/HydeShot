//======================================================
// File Name	: SphereCollider.cpp
// Summary		: ��
// Author		: Kyoya Sakamoto
//======================================================
#include "SphereCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">�o�^�����I�u�W�F�N�g</param>
/// <param name="radius">���a�̒���</param>
SphereCollider::SphereCollider(GameObject* owner, float radius)
	: Collider(owner)
	, m_radius(radius)
{
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool SphereCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool SphereCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool SphereCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool SphereCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}