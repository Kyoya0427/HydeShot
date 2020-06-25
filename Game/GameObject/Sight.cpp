//======================================================
// File Name	: Sight.cpp
// Summary		: プレイヤークラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Sight.h"



#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game\Camera\Camera.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>

#include <Game/Collider/CollisionManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Sight::Sight(Character* chara)
	: m_chara(chara)
	, m_posA()
	, m_posB()
{
	if (m_chara->GetTag() == ObjectTag::Enemy1)
		m_tag = ObjectTag::Sight01;
	if (m_chara->GetTag() == ObjectTag::Enemy2)
		m_tag = ObjectTag::Sight02;

	m_size = Vector3(0.3f, 0.1f, 7.0f);

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_sightCollider = GeometricPrimitive::CreateBox(deviceContext, m_size);
	m_collider      = std::make_unique<RayCollider>(this);

	m_enemyContact = false;
	m_wallContact  = false;
	
}


Sight::~Sight()
{
}



void Sight::Update(const DX::StepTimer& timer)
{
	timer;

	m_enemyContact = false;
	m_wallContact = false;
	
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	m_velocity = Vector3::Transform(Vector3(0.0f, 0.0f, -7.0f), quaternion);
	m_position = m_chara->GetPosition();

	m_posA = m_chara->GetPosition();
	m_posB = m_position + m_velocity;


	m_collider->SetPosA(m_posA);
	m_collider->SetPosB(m_posB);

	if (m_chara->GetTag() == ObjectTag::Enemy1)
	{	
		GameContext().Get<CollisionManager>()->Add(ObjectTag::Sight01, m_collider.get());
	}
	if (m_chara->GetTag() == ObjectTag::Enemy2)
	{
		GameContext().Get<CollisionManager>()->Add(ObjectTag::Sight02, m_collider.get());
	}
}

void Sight::Render()
{
	Quaternion rot    = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	Matrix rotMat     = Matrix::CreateFromQuaternion(rot);
	Matrix transMat   = Matrix::CreateTranslation(m_position);
	Matrix offset     = Matrix::CreateTranslation(Vector3(0.0f,0.0f,-3.5f));

	m_world  = offset *rotMat * transMat;

	m_sightCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_chara->GetColor(), nullptr, true);
}

void Sight::OnCollision(GameObject* object)
{
	if (object->GetTag() == ObjectTag::Wall)
		m_wallContact = true;
	else if (object->GetTag() != m_chara->GetTag())
		m_enemyContact = true;
}

bool Sight::GetWallContact()
{
	return m_wallContact;
}

bool Sight::GetEnemyContact()
{
	return m_enemyContact;
}
