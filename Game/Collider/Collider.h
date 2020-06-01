//======================================================
// File Name	: Collider.h
// Summary	: �Փːe�N���X
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>

class GameObject;
class SphereCollider;
class BoxCollider;

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


public:
	//����������̏���
	void HitContact(const Collider* object) const;
	// ���W���擾
	const DirectX::SimpleMath::Vector3 GetPosition() const;
	//���W��ݒ�
	 void SetPosition(DirectX::SimpleMath::Vector3 pos);
	 //����������擾
	const DirectX::SimpleMath::Vector3 GetOffset() const;
	//���������ݒ�
	void  SetOffset(const DirectX::SimpleMath::Vector3& offset);

protected:
	//�I�u�W�F�N�g
	GameObject*                  m_owner;
	//�������萔�l
	DirectX::SimpleMath::Vector3 m_offset;
};
