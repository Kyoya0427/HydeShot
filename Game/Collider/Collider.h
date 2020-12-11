//======================================================
// File Name	: Collider.h
// Summary		: �R���C�_�[�e�N���X
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK/SimpleMath.h>

#include <Game/GameObject/GameObject.h>

class GameObject;
class SphereCollider;
class BoxCollider;
class RayCollider;

class Collider
{
public:
	//�R���X�g���N�^
	Collider(GameObject* owner);
	//�f�X�g���N�^
	virtual ~Collider() = default;

public:
	//���������I�u�W�F�N�g�̎�ޔ���
	virtual bool IsCollided(const Collider*       collider) const = 0;
	virtual bool IsCollided(const SphereCollider* collider) const;
	virtual bool IsCollided(const BoxCollider*    collider) const;
	virtual bool IsCollided(const RayCollider*    collider) const;

public:
	//����������̏���
	void OnCollision(const Collider* object) const;

public:
	 //����������擾
	const DirectX::SimpleMath::Vector3& GetOffset() const   { return m_offset;}
	//�I�u�W�F�N�g���擾
	GameObject* GetGameObject()								{ return m_owner; }
	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition() const;

public:
	//���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos)  { m_owner->SetPosition(pos); }
	//���������ݒ�
	void SetOffset(const DirectX::SimpleMath::Vector3& offset) { m_offset = offset; }

private:
	//�I�u�W�F�N�g
	GameObject*                         m_owner;
	//�������萔�l
	DirectX::SimpleMath::Vector3		m_offset;

};

/// <summary>
/// ���W���擾
/// </summary>
/// <returns>���W</returns>
inline DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}