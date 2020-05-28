//======================================================
// File Name	: Character.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Common\StepTimer.h>

#include <Game\Collider\SphereCollider.h>

class Character : public GameObject
{
public:
	//�R���X�g���N
	Character(const ObjectTag tag = ObjectTag::None);
	//�f�X�g���N�^
	~Character();

public:
	// �������֐�
	void Initialize(DirectX::SimpleMath::Vector2& pos);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render(const DX::StepTimer& timer) override;
	//����������̏���
	void HitContact(GameObject* object) override;

public:
	//�O�i
	void Forward  (float speed);
	//��i
	void Backward (float speed);
	//���ɐi��
	void Leftward (float speed);
	//�E�ɐi��
	void Rightward(float speed);
	//���ɐ���
	void LeftTurn (float speed);
	//�E�ɐ���
	void RightTurn(float speed);
	//���C
	void Shooting();

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	DirectX::SimpleMath::Vector3                 m_previousPos;

	//�����蔻��
	std::unique_ptr<SphereCollider>  m_collider;
};