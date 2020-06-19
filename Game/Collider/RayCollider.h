//======================================================
// File Name	: RayCollider.h
// Summary		: ��
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class RayCollider : public Collider
{
public:
	//�R���X�g���N�^
	RayCollider(GameObject* owner);
	//�f�X�g���N�^
	~RayCollider() = default;

public:
	//���������I�u�W�F�N�g�̎�ޔ���
	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider)	const override;
	bool IsCollided(const RayCollider*    collider) const override;

public:
	DirectX::SimpleMath::Vector3 GetPosA() const;
	DirectX::SimpleMath::Vector3 GetPosB() const;
	//�T�C�Y�̎擾�Ɛݒ�
	void SetPosA(DirectX::SimpleMath::Vector3 posA);
	void SetPosB(DirectX::SimpleMath::Vector3 posB);


private:
	DirectX::SimpleMath::Vector3 m_posA;
	DirectX::SimpleMath::Vector3 m_posB;
};
