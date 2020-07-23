//======================================================
// File Name	: Sight.h
// Summary		: �Ə�
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK/PrimitiveBatch.h>

#include <Game/GameObject/GameObject.h>

#include <Game/Collider/RayCollider.h>

class Character;

class Sight : public GameObject
{
public:
	//�R���X�g���N�^
	Sight(Character* chara);
	//�f�X�g���N�^
	~Sight();

public:
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_sightCollider;
	//�����蔻��
	std::unique_ptr<RayCollider>				 m_collider;
	//�T�C�Y
	DirectX::SimpleMath::Vector3                 m_size;
	//�������Ă�L����
	Character*									 m_chara;
	//�n�_
	DirectX::SimpleMath::Vector3                 m_posA;
	//�I�_
	DirectX::SimpleMath::Vector3                 m_posB;
	//�G�Ƃ̑��΍��W
	float						                 m_enemyToDistance;

	

};

