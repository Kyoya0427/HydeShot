//======================================================
// File Name	 : ArtilleryShell.h
// Summary	 : �e
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <DirectXTK\SimpleMath.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class ArtilleryShell : public GameObject
{
public:
	//�R���X�g���N
	ArtilleryShell(const ObjectTag tag, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth);
	//�f�X�g���N�^
	~ArtilleryShell();


public:
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render(const DX::StepTimer& timer) override;
	//����������̏���
	void HitContact(GameObject* object) override;

public:
	static const float MOVE_SPEED;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// �R���C�_�[
	std::unique_ptr<SphereCollider> m_collider;
};