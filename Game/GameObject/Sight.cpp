//======================================================
// File Name	: Sight.cpp
// Summary		: 照準
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
	: GameObject()
	, m_sightCollider()
	, m_size()
	, m_chara(chara)
	, m_posA()
	, m_posB()
	, m_enemyToDistance()
	, m_wallToDistance()

{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	//タグを設定
	if (m_chara->GetTag() == ObjectTag::Enemy1)
		m_tag = ObjectTag::Sight01;
	if (m_chara->GetTag() == ObjectTag::Enemy2)
		m_tag = ObjectTag::Sight02;

	m_size = Vector3(0.3f, 0.1f, 9.0f);

	m_sightCollider = GeometricPrimitive::CreateBox(deviceContext, m_size);
	m_collider      = std::make_unique<RayCollider>(this);

	m_chara->SetEnemySightContact(false);
	m_chara->SetWallSightContact(false);
	
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

	m_chara->SetEnemySightContact(false);
	m_chara->SetWallSightContact(false);
	m_enemyToDistance = 0.0f;
	m_wallToDistance  = 0.0f;

	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	m_velocity = Vector3::Transform(Vector3(0.0f, 0.0f, -m_size.z), quaternion);
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
	Matrix offset = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, -m_size.z / 2.0f));

	m_world = offset * rotMat * transMat;

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
	{
		m_chara->SetWallSightContact(true);
		m_wallToDistance = Vector3::Distance(m_chara->GetPosition(), object->GetPosition());		
	}
	else if (object->GetTag() != m_chara->GetTag())
	{
		m_chara->SetEnemySightContact(true);
		m_enemyToDistance = Vector3::Distance(m_chara->GetPosition(), object->GetPosition());
	}

	if (m_chara->GetWallSightContact() && m_enemyToDistance != 0.0f)
	{
		if (m_enemyToDistance < m_wallToDistance)
			m_chara->SetWallSightContact(false);

	}

	if (m_chara->GetEnemySightContact() && m_wallToDistance != 0.0f)
	{
		if (m_enemyToDistance > m_wallToDistance)
			m_chara->SetEnemySightContact(false);
	}	
}