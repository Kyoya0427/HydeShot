//======================================================
// File Name	: SphereCollider.h
// Summary	: ��
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	//�R���X�g���N�^
	SphereCollider(GameObject* owner, float radius = 1.0f);
	//�f�X�g���N�^
	~SphereCollider() = default;

public:
	//���������I�u�W�F�N�g�̎�ޔ���

	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider) const override;

public:
	//���a���擾
	float GetRadius() const;
	//���a��ݒ�
	void  SetRadius(float radius);
private:
	//���a
	float m_radius;

};
