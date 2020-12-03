//======================================================
// File Name	: Bullet.cpp
// Summary		: �e
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bullet.h"

#include <Game/Common/GameContext.h>

#include <Game/Camera/Camera.h>
			  
#include <Game/Collider/SphereCollider.h>
#include <Game/Collider/CollisionManager.h>

const float Bullet::MOVE_SPEED = 0.2f;
const float Bullet::RADIUS     = 0.3f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�I�u�W�F�N�g��</param>
/// <param name="position">���W</param>
/// <param name="azimuth">�L�����̌����Ă���p</param>
Bullet::Bullet(const ObjectTag& tag, const ObjectTag& charaTag,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth)
	: GameObject(tag)
	, m_collider()
{
	//�����ݒ�
	m_position   = position;
	m_velocity.z = -MOVE_SPEED;
	m_velocity   = DirectX::SimpleMath::Vector3::Transform(m_velocity, azimuth);
	m_charaTag   = charaTag;
	m_radius     = RADIUS;
	m_color      = DirectX::Colors::Silver;
	m_collider   = std::make_unique<SphereCollider>(this, m_radius);

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
	GameContext::Get<CollisionManager>()->Add(m_tag, m_collider.get());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bullet::Render()
{
	//���[���h���W�𐶐�
	DirectX::SimpleMath::Matrix transMat = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_world = transMat;

	//���f����`��
	m_sphereModel->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Bullet::OnCollision(GameObject* object)
{
	object;
	if (m_charaTag != object->GetTag())
	{
		Destroy(this);
	}
}