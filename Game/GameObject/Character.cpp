//======================================================
// File Name	: Character.cpp
// Summary		: �v���C���[�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Character.h"

#include <Game/Common\GameContext.h>
#include <Game/Common\DeviceResources.h>
#include <Game/Common/DebugFont.h>
			  
#include <Game/Camera\Camera.h>
			  
#include <Game/GameObject\GameObjectManager.h>
#include <Game/GameObject\ObjectManager.h>
#include <Game/GameObject\Bullet.h>
#include <Game/GameObject/Sight.h>
			  
#include <Game/Collider\CollisionManager.h>
			  
#include <Game/GameState/GameStateManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int Character::MAX_HP = 5;

/// <summary>
/// �R���X�g���N
/// </summary>
Character::Character(const ObjectTag tag)
	: GameObject(tag)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Character::~Character()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�������W</param>
void Character::Initialize(DirectX::SimpleMath::Vector2 & pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
	m_position = Vector3((float)m_x, 0.0f, (float)m_y);
	m_radius = 0.4f;

	m_hp = MAX_HP;

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	m_model = GeometricPrimitive::CreateCone(deviceContext);

	m_sphereCollider = GeometricPrimitive::CreateSphere(deviceContext,1.0f,8U);
	m_collider = std::make_unique<SphereCollider>(this, m_radius);

	
	m_sight = std::make_unique<Sight>(this);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Character::Update(const DX::StepTimer & timer)
{
	timer;
	m_previousPos = m_position;
	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, quaternion);


	m_position += m_velocity;
	m_velocity = Vector3::Zero;

	m_sight->Update(timer);
}

/// <summary>
/// �`��
/// </summary>
void Character::Render()
{
	m_world = Matrix::Identity;
	Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix r = Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90.0f));
	Matrix rotMat = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ���[���h�s����쐬

	Matrix w = scalemat * r * rotMat * transMat;

	m_model->Draw(w, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);

	Matrix world = rotMat * transMat;

	m_sphereCollider->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);

	m_sight->Render();
}
/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object"></param>
void Character::OnCollision(GameObject* object)
{
	object;
	if (object->GetTag() == GameObject::ObjectTag::Wall)
	{
		m_position = m_previousPos;
		m_velocity = Vector3::Zero;
	
	}

	if (object->GetTag() == GameObject::ObjectTag::Bullet)
	{
		if (object->GetCharaTag() != GetTag())
		{
			m_hp -= 1;
		}
	}

	if (m_hp <= 0)
	{
		Destroy(this);
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}

}

/// <summary>
/// �O�i
/// </summary>
/// <param name="speed"></param>
void Character::Forward(float speed)
{
	m_velocity.z = -speed;

}
/// <summary>
/// ��i
/// </summary>
/// <param name="speed"></param>
void Character::Backward(float speed)
{
	m_velocity.z = speed;

}

/// <summary>
/// ���ɐi��
/// </summary>
/// <param name="speed"></param>
void Character::Leftward(float speed)
{
	m_velocity.x = -speed;

}

/// <summary>
/// �E�ɐi��
/// </summary>
/// <param name="speed"></param>
void Character::Rightward(float speed)
{
	m_velocity.x = speed;
}

/// <summary>
/// ���ɐ���
/// </summary>
/// <param name="speed"></param>
void Character::LeftTurn(float speed)
{
	m_rotation.y += speed;
}

/// <summary>
/// �E�ɐ���
/// </summary>
/// <param name="speed"></param>
void Character::RightTurn(float speed)
{
	m_rotation.y -= speed;
}

/// <summary>
/// ���C
/// </summary>
void Character::Shoot()
{
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	std::unique_ptr<Bullet> shell = std::make_unique<Bullet>(ObjectTag::Bullet, GetTag(),m_position, rot);
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(shell));
}

int Character::GetHp()
{
	return m_hp;
}

bool Character::GetWallContact()
{
	return m_wallContact;
}

void Character::SetWallContact(bool contact)
{
	m_wallContact = contact;
}

bool Character::GetEnemyContact()
{
	return m_enemyContact;
}

void Character::SetEnemyContact(bool contact)
{
	m_enemyContact = contact;
}
                                                           