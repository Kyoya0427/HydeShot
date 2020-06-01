//======================================================
// File Name	: SphereCollider.cpp
// Summary	: ��
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "SphereCollider.h"

#include <Game\Collider\CollisionManager.h>

#include <Game\GameObject\GameObject.h>

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
/// ���a��ݒ�
/// </summary>
/// <param name="radius"></param>
void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}

/// <summary>
/// ���a�擾
/// </summary>
/// <returns></returns>
float SphereCollider::GetRadius() const
{
	return m_radius;
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
