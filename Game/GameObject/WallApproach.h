//======================================================
// File Name	: WallApproach.h
// Summary		: �ǂɐڋ߂��Ă��邩
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK/PrimitiveBatch.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/WallApproachVelID.h>

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

public:
	void SetOffsetAngle(float angle);
	//�ǂɐڋ߂��Ă��邩
	WallApproachVelID GetWallApproach();
	//�ǂɐڋ߂��Ă��邩
	void SetWallApproach(WallApproachVelID approach);

public:
	static const float  FORWARD_ANGLE;
	static const float  BACKWARD_ANGLE;
	static const float  LEFT_ANGLE;
	static const float  RIGHT_ANGLE;

private:
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_WallApproachCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>				 m_collider;
	//�T�C�Y
	DirectX::SimpleMath::Vector3                 m_size;
	//�������Ă�L����
	Character*									 m_chara;

	float                                        m_offsetAngle;

	WallApproachVelID							 m_isWallApproach;
};

