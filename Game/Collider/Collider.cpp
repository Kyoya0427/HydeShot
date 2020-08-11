//======================================================
// File Name	: Collider.cpp
// Summary		: �R���C�_�[�e�N���X
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "Collider.h"

#include <Game/GameObject/GameObject.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">�o�^�����I�u�W�F�N�g</param>
Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset()
{
}

/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool Collider::IsCollided(const SphereCollider* collider) const
{
	collider;
	return false;
}

/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool Collider::IsCollided(const BoxCollider* collider) const
{
	collider;

	return false;
}

/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
bool Collider::IsCollided(const RayCollider* collider) const
{
	collider;

	return false;
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Collider::OnCollision(const Collider* object) const
{
	m_owner->OnCollision(object->m_owner);
}
