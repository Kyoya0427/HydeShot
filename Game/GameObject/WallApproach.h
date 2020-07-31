//======================================================
// File Name	: WallApproach.h
// Summary		: �ǂɐڋ߂��Ă��邩
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK/PrimitiveBatch.h>

#include <Game/GameObject/GameObject.h>

#include <Game/Collider/BoxCollider.h>

class Character;

class WallApproach : public GameObject
{
public:
	//�R���X�g���N�^
	WallApproach(Character* chara);
	//�f�X�g���N�^
	~WallApproach();

public:
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_WallApproachCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>				 m_collider;
	//�T�C�Y
	DirectX::SimpleMath::Vector3                 m_size;
	//�������Ă�L����
	Character*									 m_chara;
	//�G�Ƃ̑��΍��W
	float						                 m_enemyToDistance;
	//�ǂƂ̑��΍��W
	float						                 m_wallToDistance;

};

