//======================================================
// File Name	 : Bullet.cpp
// Summary	 : �e
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bullet.h"

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\Collider\SphereCollider.h>
#include <Game\Collider\CollisionManager.h>

//�萔�̐ݒ�
const float Bullet::MOVE_SPEED = 0.2f;

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�I�u�W�F�N�g��</param>
/// <param name="position">���W</param>
/// <param name="azimuth">�L�����̌����Ă���p</param>
Bullet::Bullet(const ObjectTag tag, const ObjectTag charaTag,const Vector3& position, const Quaternion& azimuth)
	: GameObject(tag)
{
	//�f�o�C�X�R���e�L�X�g���擾
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	//�����ݒ�
	m_position = position;
	m_velocity.z = -MOVE_SPEED;
	m_velocity = Vector3::Transform(m_velocity, azimuth);
	m_charaTag = charaTag;
	m_radius = 0.3f;
	m_color = Colors::Silver;
	m_sphereModel = GeometricPrimitive::CreateSphere(deviceContext, m_radius);
	m_collider = std::make_unique<SphereCollider>(this, m_radius);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bullet::~Bullet()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bullet::Update(const DX::StepTimer& timer)
{
	timer;
	//���W���ړ�
	
	m_position += m_velocity;

	// �Փ˔���}�l�[�W���[�ɓo�^
	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bullet::Render()
{
	//���[���h���W�𐶐�
	Matrix world = Matrix::Identity;
	Matrix transMat = Matrix::CreateTranslation(m_position);
	
	world = transMat;
	//���f����`��
	m_sphereModel->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Bullet::HitContact(GameObject* object)
{
	object;
	if (m_charaTag != object->GetTag())
	{
		Destroy(this);
	}
}