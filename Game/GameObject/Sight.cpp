//======================================================
// File Name	: Sight.cpp
// Summary		: 照準
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Sight.h"

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game/Camera/Camera.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>

#include <Game/Collider/CollisionManager.h>

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="chara">所持してるキャラ</param>
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

	m_chara->SetEnemyContact(false);
	m_chara->SetWallContact(false);
	
}

/// <summary>
/// デストラクタ
/// </summary>
Sight::~Sight()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Sight::Update(const DX::StepTimer& timer)
{
	timer;

	m_chara->SetEnemyContact(false);
	m_chara->SetWallContact(false);
	
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

/// <summary>
/// 描画
/// </summary>
void Sight::Render()
{
	Quaternion rot    = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	Matrix rotMat     = Matrix::CreateFromQuaternion(rot);
	Matrix transMat   = Matrix::CreateTranslation(m_position);
	Matrix offset     = Matrix::CreateTranslation(Vector3(0.0f,0.0f,-3.5f));

	m_world  = offset *rotMat * transMat;

	if (PlayState::m_isDebug)
	m_sightCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_chara->GetColor(), nullptr, true);
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object"></param>
void Sight::OnCollision(GameObject* object)
{
	if (object->GetTag() == ObjectTag::Wall)
		m_chara->SetWallContact(true);
	else if (object->GetTag() != m_chara->GetTag())
		m_chara->SetEnemyContact(true);
}


