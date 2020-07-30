//======================================================
// File Name	: Character.cpp
// Summary		: キャラクター
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Character.h"

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>
			  
#include <Game/Camera/Camera.h>
			  
#include <Game/GameObject/GameObjectManager.h>
#include <Game/GameObject/ObjectManager.h>
#include <Game/GameObject/Bullet.h>
#include <Game/GameObject/Sight.h>
#include <Game/GameObject/WallApproach.h>
			  
#include <Game/Collider/CollisionManager.h>
			  
#include <Game/GameState/GameStateManager.h>
#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int Character::MAX_HP = 5;

/// <summary>
/// コンストラク
/// </summary>
Character::Character(const ObjectTag tag)
	: GameObject(tag)
	, m_model()
	, m_sphereCollider()
	, m_sight()
	, m_wallApproach()
	, m_collider()
	, m_previousPos()
	, m_wallSightContact(false)
	, m_wallContact(false)
	, m_enemySightContact(false)
	, m_isWallApproach(false)
	, m_hp()
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
	
	m_hp = MAX_HP;
	m_wallContact = false;

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	m_model = GeometricPrimitive::CreateCone(deviceContext);

	m_sphereCollider = GeometricPrimitive::CreateSphere(deviceContext,1.0f,8U);
	m_collider = std::make_unique<SphereCollider>(this, m_radius);

	m_sight = std::make_unique<Sight>(this);
	m_wallApproach = std::make_unique<WallApproach>(this);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Character::Update(const DX::StepTimer & timer)
{
	timer;
	m_wallContact = false;
	m_previousPos = m_position;

	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, quaternion);


	m_position += m_velocity;
	m_velocity = Vector3::Zero;



	m_sight->Update(timer);
	m_wallApproach->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
void Character::Render()
{
	Quaternion rot = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix r = Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90.0f));
	Matrix rotMat = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ワールド行列を作成
	DebugFont* debugFont = DebugFont::GetInstance();

	if (m_tag == GameObject::ObjectTag::Player)
	{
		if (m_isWallApproach)
		{
			debugFont->print(700, 310, L"Player = true");
			debugFont->draw();
		}
		else
		{
			debugFont->print(700, 310, L"Player = false");
			debugFont->draw();
		}
	}
	if (m_tag == GameObject::ObjectTag::Enemy1)
	{
		if (m_isWallApproach)
		{
			debugFont->print(700, 340, L"Enemy1 = true");
			debugFont->draw();
		}
		else
		{
			debugFont->print(700, 340, L"Enemy1 = false");
			debugFont->draw();
		}
	}

	m_world = scalemat * r * rotMat * transMat;

	m_model->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);

	Matrix world = rotMat * transMat;

	if(PlayState::m_isDebug)
	m_sphereCollider->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);

	m_sight->Render();
	m_wallApproach->Render();
}
/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object"></param>
void Character::OnCollision(GameObject* object)
{
	object;
	if (object->GetTag() == GameObject::ObjectTag::Wall)
	{
		m_position = m_previousPos;
		m_velocity = Vector3::Zero;
		m_wallContact = true;
	}

	if (object->GetTag() == GameObject::ObjectTag::Bullet)
	{
		if (object->GetCharaTag() != GetTag())
		{
			m_hp -= 1;
		}
	}

	if (m_hp <= 0)
	{
		Destroy(this);
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}

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
	std::unique_ptr<Bullet> shell = std::make_unique<Bullet>(ObjectTag::Bullet, GetTag(),m_position, rot);
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(shell));
}

/// <summary>
/// hpを取得
/// </summary>
/// <returns></returns>
int Character::GetHp()
{
	return m_hp;
}

/// <summary>
/// 壁に接触してるか
/// </summary>
/// <returns></returns>
bool Character::GetWallSightContact()
{
	return m_wallSightContact;
}

bool Character::GetWallContact()
{
	return m_wallContact;
}

/// <summary>
/// 設定
/// </summary>
/// <param name="contact"></param>
void Character::SetWallSightContact(bool contact)
{
	m_wallSightContact = contact;
}

/// <summary>
/// 敵に接触しているか
/// </summary>
/// <returns></returns>
bool Character::GetEnemySightContact()
{
	return m_enemySightContact;
}

/// <summary>
/// 設定
/// </summary>
/// <param name="contact"></param>
void Character::SetEnemySightContact(bool contact)
{
	m_enemySightContact = contact;
}

bool Character::GetWallApproach()
{
	return m_isWallApproach;
}

void Character::SetWallApproach(bool approach)
{
	m_isWallApproach = approach;
}

Sight* Character::GetSight()
{
	return m_sight.get();
}
                                                           