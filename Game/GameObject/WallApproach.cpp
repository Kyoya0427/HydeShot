//======================================================
// File Name	: WallApproach.cpp
// Summary		: 壁に接近しているか
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallApproach.h"

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game/Camera/Camera.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>
#include <Game/GameObject/WallApproachVelID.h>

#include <Game/Collider/CollisionManager.h>

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float WallApproach::FORWARD_ANGLE = 0.0f;
const float WallApproach::BACKWARD_ANGLE = -XM_PI;
const float WallApproach::LEFT_ANGLE = XM_PI / 2;
const float WallApproach::RIGHT_ANGLE = -XM_PI / 2;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="chara">所持してるキャラ</param>
WallApproach::WallApproach(Character* chara)
	: GameObject()
	, m_WallApproachCollider()
	, m_size()
	, m_chara(chara)
	, m_offsetAngle()
{
	m_tag = ObjectTag::WallApproach;
	m_size = Vector3(0.3f, 0.1f, 0.8f);

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_WallApproachCollider = GeometricPrimitive::CreateBox(deviceContext, m_size);
	m_collider      = std::make_unique<BoxCollider>(this,m_size);
	
}

/// <summary>
/// デストラクタ
/// </summary>
WallApproach::~WallApproach()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void WallApproach::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::NONE);
	m_chara->SetWallFlont(false);

	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRadiansY() + m_offsetAngle);
	m_velocity = Vector3::Transform(Vector3(0.0f, 0.0f, -m_size.z), quaternion);
	m_position = m_chara->GetPosition();

	m_position += m_velocity;

	m_collider->SetPosition(m_position);

	
	
	GameContext().Get<CollisionManager>()->Add(ObjectTag::WallApproach, m_collider.get());
	
}

/// <summary>
/// 描画
/// </summary>
void WallApproach::Render()
{
	Quaternion rot    = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRadiansY() + m_offsetAngle);
	Matrix rotMat     = Matrix::CreateFromQuaternion(rot);
	Matrix transMat   = Matrix::CreateTranslation(m_position);

	m_world  = rotMat * transMat;
	
	if (PlayState::m_isDebug)
	{
		m_WallApproachCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Green, nullptr, true);
	}
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object"></param>
void WallApproach::OnCollision(GameObject* object)
{
	object;
	m_chara->SetWallFlont(true);
	if (m_offsetAngle == FORWARD_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::FORWARD);
	if (m_offsetAngle == BACKWARD_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::BACKWARD);
	if (m_offsetAngle == LEFT_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::LEFTWARD);
	if (m_offsetAngle == RIGHT_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::RIGHTWARD);
}

void WallApproach::SetOffsetAngle(float angle)
{
	m_offsetAngle = angle;
}

WallApproachVelID WallApproach::GetWallApproach()
{
	return m_isWallApproach;
}

void WallApproach::SetWallApproach(WallApproachVelID approach)
{
	m_isWallApproach = approach;
}


