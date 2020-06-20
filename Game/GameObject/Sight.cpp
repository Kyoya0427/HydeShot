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
{
	if (m_chara->GetTag() == ObjectTag::Enemy1)
		m_tag = ObjectTag::Sight01;
	if (m_chara->GetTag() == ObjectTag::Enemy2)
		m_tag = ObjectTag::Sight02;

	m_size = Vector3(0.3f, 0.1f, 7.0f);

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_sightCollider = GeometricPrimitive::CreateBox(deviceContext, m_size);
	m_collider      = std::make_unique<RayCollider>(this);
	m_contact = false;

	m_posA = m_chara->GetPosition();
}


Sight::~Sight()
{
}



void Sight::Update(const DX::StepTimer& timer)
{
	timer;
	m_contact = false;
	
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	m_velocity = Vector3::Transform(Vector3(0.0f, 0.0f, -7.0f), quaternion);
	m_position = m_chara->GetPosition();
	m_posB = m_position + m_velocity;


	m_collider->SetPosA(m_posA);
	m_collider->SetPosB(m_posB);

	if (m_chara->GetTag() == ObjectTag::Enemy1)
	{	
		GameContext().Get<CollisionManager>()->Add(ObjectTag::Sight01, m_collider.get());
	}
	if (m_chara->GetTag() == ObjectTag::Enemy2);
	{
		GameContext().Get<CollisionManager>()->Add(ObjectTag::Sight02, m_collider.get());
	}
}

void Sight::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	Quaternion rot    = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	Matrix rotMat     = Matrix::CreateFromQuaternion(rot);
	Matrix transMat   = Matrix::CreateTranslation(m_position);
	Matrix offset     = Matrix::CreateTranslation(Vector3(0.0f,0.0f,-3.5f));

	m_world  = offset *rotMat * transMat;

	m_sightCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_chara->GetColor(), nullptr, true);
	if (GetTag() == ObjectTag::Sight01)
	{
		
		/*if (m_contact == true) 
		{
			debugFont->print(500, 30, L" true");
			debugFont->draw();
		}
		else
		{
			debugFont->print(500, 30, L"false");
			debugFont->draw();
		}*/

	}
}

void Sight::OnCollision(GameObject* object)
{
	if(object->GetTag() == ObjectTag::Enemy1 && GetTag() == ObjectTag::Sight02)
	m_contact = true;
	if(object->GetTag() == ObjectTag::Enemy2 && GetTag() == ObjectTag::Sight01)
	m_contact = true;
	/*if(object->GetTag() == ObjectTag::Wall && GetTag() == ObjectTag::Sight02)
	m_contact = true;
	if(object->GetTag() == ObjectTag::Wall && GetTag() == ObjectTag::Sight01)
	m_contact = true;*/
}
