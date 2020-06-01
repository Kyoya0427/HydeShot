//======================================================
// File Name	: Collider.cpp
// Summary	: �Փːe�N���X
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "Collider.h"

#include <Game\GameObject\GameObject.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">�o�^�����I�u�W�F�N�g</param>
Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool Collider::IsCollided(const SphereCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");
	collider;
	return false;
}

/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="collider">�I�u�W�F�N�g</param>
/// <returns></returns>
bool Collider::IsCollided(const BoxCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");
	collider;

	return false;
}

/// <summary>
///  ����������̏���
/// </summary>
/// <param name="object"></param>
void Collider::HitContact(const Collider* object) const
{
	m_owner->HitContact(object->m_owner);
}

/// <summary>
/// ���W���擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}

/// <summary>
/// ���W��ݒ�
/// </summary>
/// <param name="pos"></param>
void Collider::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	m_owner->SetPosition(pos);
}

/// <summary>
/// ����������擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
{
	return m_offset;
}

/// <summary>
/// ���������ݒ�
/// </summary>
/// <param name="offset"></param>
void Collider::SetOffset(const DirectX::SimpleMath::Vector3 & offset)
{
	m_offset = offset;
}
