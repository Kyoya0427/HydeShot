//======================================================
// File Name	: Character.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Character.h"

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\Bullet.h>

#include <Game\Collider\CollisionManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラク
/// </summary>
Character::Character(const ObjectTag tag)
	: GameObject(tag)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Character::~Character()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">初期座標</param>
void Character::Initialize(DirectX::SimpleMath::Vector2 & pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
	m_position = Vector3((float)m_x, 0.0f, (float)m_y);
	m_radius = 0.4f;
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_model = GeometricPrimitive::CreateCone(deviceContext);

	m_sphereCollider = GeometricPrimitive::CreateSphere(deviceContext,1.0f,8U);

	m_collider = std::make_unique<SphereCollider>(this, m_radius);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Character::Update(const DX::StepTimer & timer)
{
	timer;
	m_previousPos = m_position;

	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, quaternion);

	m_position += m_velocity;
	m_velocity = Vector3::Zero;

	
}

/// <summary>
/// 描画
/// </summary>
void Character::Render()
{
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);


	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix r        = Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90.0f));
	Matrix rotMat   = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ワールド行列を作成

	m_world = scalemat * r * rotMat * transMat;

	m_model->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);

	Matrix world = rotMat * transMat;
	m_sphereCollider->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);

	
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object"></param>
void Character::HitContact(GameObject* object)
{
	object;
	m_position = m_previousPos;
	m_velocity = Vector3::Zero;
}

/// <summary>
/// 前進
/// </summary>
/// <param name="speed"></param>
void Character::Forward(float speed)
{
	m_velocity.z = -speed;

}
/// <summary>
/// 後進
/// </summary>
/// <param name="speed"></param>
void Character::Backward(float speed)
{
	m_velocity.z = speed;

}

/// <summary>
/// 左に進む
/// </summary>
/// <param name="speed"></param>
void Character::Leftward(float speed)
{
	m_velocity.x = -speed;

}

/// <summary>
/// 右に進む
/// </summary>
/// <param name="speed"></param>
void Character::Rightward(float speed)
{
	m_velocity.x = speed;
	
}

/// <summary>
/// 左に旋回
/// </summary>
/// <param name="speed"></param>
void Character::LeftTurn(float speed)
{
	m_rotation.y += speed;
}

/// <summary>
/// 右に旋回
/// </summary>
/// <param name="speed"></param>
void Character::RightTurn(float speed)
{
	m_rotation.y -= speed;
}

/// <summary>
/// 発砲
/// </summary>
void Character::Shoot()
{
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);

	std::unique_ptr<Bullet> shell = std::make_unique<Bullet>(ObjectTag::Bullet,m_position, rot);
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(shell));
}
