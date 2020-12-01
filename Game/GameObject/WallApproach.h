//======================================================
// File Name	: WallApproach.h
// Summary		: �ǂɐڋ߂��Ă��邩
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
	//�ǂɐڋ߂��Ă��邩
	const WallApproachVelID& GetWallApproach() const        { return m_isWallApproach; }

public:
	//�ǂɐڋ߂��Ă��邩�ݒ�
	void SetWallApproach(const WallApproachVelID& approach) { m_isWallApproach = approach; }
	//�I�t�Z�b�g��ݒ�
	void SetOffsetAngle(const float angle)                  { m_offsetAngle = angle; }
	

public:
	//�O�̊p�x
	static const float  FORWARD_ANGLE;
	//���̊p�x
	static const float  BACKWARD_ANGLE;
	//���̊p�x
	static const float  LEFT_ANGLE;
	//�E�̊p�x
	static const float  RIGHT_ANGLE;

private:
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive>	m_WallApproachCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>				    m_collider;
	//�T�C�Y
	DirectX::SimpleMath::Vector3                    m_size;
	//�������Ă�L����
	Character*									    m_chara;
	//�I�t�Z�b�g�p�x
	float                                           m_offsetAngle;
	//�ړ�����
	WallApproachVelID							    m_isWallApproach;

};