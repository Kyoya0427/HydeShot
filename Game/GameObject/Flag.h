//======================================================
// File Name	: Flag.h
// Summary		: ��
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK\GeometricPrimitive.h>
#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class Flag : public GameObject
{
public:
	//�R���X�g���N�^
	Flag(const ObjectTag tag = ObjectTag::None);
	//�f�X�g���N�^
	~Flag();
public:
	// �������֐�
	void Initialize(int x, int y);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	//�����蔻��
	std::unique_ptr<SphereCollider>				 m_collider;

};