//======================================================
// File Name	: BoxCollider.h
// Summary		: ��
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	//�R���X�g���N�^
	BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	//�f�X�g���N�^
	~BoxCollider() = default;

public:
	//���������I�u�W�F�N�g�̎�ޔ���
	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider) const override;


public:
	//�T�C�Y�̎擾�Ɛݒ�
	void SetSize(const DirectX::SimpleMath::Vector3& size);
	const DirectX::SimpleMath::Vector3& GetSize() const;

private:
	//�T�C�Y
	DirectX::SimpleMath::Vector3 m_size;
};
