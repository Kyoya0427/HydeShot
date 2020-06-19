//======================================================
// File Name	: RayCollider.cpp
// Summary		: ���C
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "RayCollider.h"

#include <Game\Collider\CollisionManager.h>

#include <Game\GameObject\GameObject.h>

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
/// <returns></returns>
bool RayCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool RayCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

bool RayCollider::IsCollided(const BoxCollider* collider) const
{
	return  CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool RayCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
/// A���W���擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 RayCollider::GetPosA() const
{
	return m_posA;
}

/// <summary>
/// B���W���擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 RayCollider::GetPosB() const
{
	return m_posB;
}

/// <summary>
/// A���W��ݒ�
/// </summary>
/// <param name="posA"></param>
void RayCollider::SetPosA(DirectX::SimpleMath::Vector3 posA)
{
	m_posA = posA;
}

/// <summary>
/// B���W�ɐݒ�
/// </summary>
/// <param name="posB"></param>
void RayCollider::SetPosB(DirectX::SimpleMath::Vector3 posB)
{
	m_posB = posB;
}


