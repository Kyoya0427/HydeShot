//======================================================
// File Name	: Bullet.cpp
// Summary		: 弾
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
/// コンストラクタ
/// </summary>
/// <param name="tag">オブジェクト名</param>
/// <param name="position">座標</param>
/// <param name="azimuth">キャラの向いてる方角</param>
Bullet::Bullet(const ObjectTag& tag, const ObjectTag& charaTag,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth)
	: GameObject(tag)
	, m_collider()
{
	//初期設定
	m_position   = position;
	m_velocity.z = -MOVE_SPEED;
	m_velocity   = DirectX::SimpleMath::Vector3::Transform(m_velocity, azimuth);
	m_charaTag   = charaTag;
	m_radius     = RADIUS;
	m_color      = DirectX::Colors::Silver;
	m_collider   = std::make_unique<SphereCollider>(this, m_radius);

}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="timer">タイマー</param>
void Bullet::Update(const DX::StepTimer& timer)
{
	timer;
	//座標を移動
	m_position += m_velocity;
	// 衝突判定マネージャーに登録
	GameContext::Get<CollisionManager>()->Add(m_tag, m_collider.get());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer">タイマー</param>
void Bullet::Render()
{
	//ワールド座標を生成
	DirectX::SimpleMath::Matrix transMat = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_world = transMat;

	//モデルを描画
	m_sphereModel->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Bullet::OnCollision(GameObject* object)
{
	object;
	if (m_charaTag != object->GetTag())
	{
		Destroy(this);
	}
}