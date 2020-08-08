//======================================================
// File Name	: BoxCollider.cpp
// Summary		: ��
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "BoxCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">�o�^�����I�u�W�F�N�g</param>
/// <param name="size">��ӂ̔����̒���</param>
BoxCollider::BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size)
	: Collider(owner)
	, m_size(size)
{
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
