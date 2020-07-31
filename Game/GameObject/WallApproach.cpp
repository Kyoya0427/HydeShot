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

#include <Game/Collider/CollisionManager.h>

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="chara">所持してるキャラ</param>
WallApproach::WallApproach(Character* chara)
	: GameObject()
	, m_WallApproachCollider()
	, m_size()
	, m_chara(chara)
	, m_enemyToDistance()

{
	m_tag = ObjectTag::WallApproach;
	m_size = Vector3(0.3f, 0.1f, 1.5f);

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
	m_chara->SetWallApproach(false);

	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	m_velocity = Vector3::Transform(Vector3(0.0f, 0.0f, -1.5f), quaternion);
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
	Quaternion rot    = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_chara->GetRotation().y);
	Matrix rotMat     = Matrix::CreateFromQuaternion(rot);
	Matrix transMat   = Matrix::CreateTranslation(m_position);

	m_world  = rotMat * transMat;

	if (PlayState::m_isDebug)
		m_WallApproachCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Green, nullptr, true);
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object"></param>
void WallApproach::OnCollision(GameObject* object)
{
	m_chara->SetWallApproach(true);
}


