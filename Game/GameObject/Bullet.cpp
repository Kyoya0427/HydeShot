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
	SetPosition(position);
	SetVelocityZ(-MOVE_SPEED);
	SetVelocity(DirectX::SimpleMath::Vector3::Transform(GetVelocity(), azimuth));
	SetCharaTag(charaTag);
	SetRadius(RADIUS);
	DirectX::SimpleMath::Color color = DirectX::Colors::Silver;
	SetColor(color);
	m_collider   = std::make_unique<SphereCollider>(this, GetRadius());

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
	SetPosition(GetPosition() + GetVelocity());
	// 衝突判定マネージャーに登録
	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer">タイマー</param>
void Bullet::Render()
{
	//ワールド座標を生成
	DirectX::SimpleMath::Matrix transMat = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	SetWorld(transMat);
	//モデルを描画
	m_sphereModel->Draw(GetWorld(), GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), GetColor());
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Bullet::OnCollision(GameObject* object)
{
	object;
	if (GetCharaTag() != object->GetTag())
	{
		Destroy(this);
	}
}