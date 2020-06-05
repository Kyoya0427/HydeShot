//======================================================
// File Name	 : Bullet.cpp
// Summary	 : 弾
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bullet.h"

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\Collider\SphereCollider.h>
#include <Game\Collider\CollisionManager.h>

//定数の設定
const float Bullet::MOVE_SPEED = 0.2f;

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">オブジェクト名</param>
/// <param name="position">座標</param>
/// <param name="azimuth">キャラの向いてる方角</param>
Bullet::Bullet(const ObjectTag tag, const ObjectTag charaTag,const Vector3& position, const Quaternion& azimuth)
	: GameObject(tag)
{
	//デバイスコンテキストを取得
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	//初期設定
	m_position = position;
	m_velocity.z = -MOVE_SPEED;
	m_velocity = Vector3::Transform(m_velocity, azimuth);
	m_charaTag = charaTag;
	m_radius = 0.3f;
	m_color = Colors::Silver;
	m_sphereModel = GeometricPrimitive::CreateSphere(deviceContext, m_radius);
	m_collider = std::make_unique<SphereCollider>(this, m_radius);

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
	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer">タイマー</param>
void Bullet::Render()
{
	//ワールド座標を生成
	Matrix world = Matrix::Identity;
	Matrix transMat = Matrix::CreateTranslation(m_position);
	
	world = transMat;
	//モデルを描画
	m_sphereModel->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Bullet::HitContact(GameObject* object)
{
	object;
	if (m_charaTag != object->GetTag())
	{
		Destroy(this);
	}
}