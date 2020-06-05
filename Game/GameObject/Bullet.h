//======================================================
// File Name	 : Bullet.h
// Summary	 : �e
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <DirectXTK\SimpleMath.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class Bullet : public GameObject
{
public:
	//�R���X�g���N
	Bullet(const ObjectTag tag, const ObjectTag charaTag,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth);
	//�f�X�g���N�^
	~Bullet();

public:
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void HitContact(GameObject* object) override;

public:
	//�e�̃X�s�[�h
	static const float MOVE_SPEED;

private:
	//�e�̃��f��
	std::unique_ptr<DirectX::GeometricPrimitive>  m_sphereModel;
	// �R���C�_�[
	std::unique_ptr<SphereCollider> m_collider;

	
};