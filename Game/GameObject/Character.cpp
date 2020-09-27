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
#include <Game/GameState/ResultState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const int   Character::MAX_HP = 5;
const float Character::INVINCIBLE_TIME = 2.0f;

/// <summary>
/// コンストラク
/// </summary>
Character::Character(const ObjectTag tag)
	: GameObject(tag)
	, m_model()
	, m_sphereCollider()
	, m_bulletModel()
	, m_sight()
	, m_wallApproach()
	, m_collider()
	, m_previousPos()
	, m_isWallSightContact(false)
	, m_isWallContact(false)
	, m_isEnemySightContact(false)
	, m_isWallDiscovery(false)
	, m_isDamage(false)
	, m_hp()
	, m_state(CharaStateID::NONE)
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
void Character::Initialize(const DirectX::SimpleMath::Vector2& pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
	m_position = Vector3((float)m_x, 0.0f, (float)m_y);
	m_radius = 0.4f;
	
	m_hp = MAX_HP;
	m_invincibleTime = INVINCIBLE_TIME;

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	m_model = GeometricPrimitive::CreateCone(deviceContext);

	m_sphereCollider = GeometricPrimitive::CreateSphere(deviceContext,1.0f,8U);
	m_bulletModel    = GeometricPrimitive::CreateSphere(deviceContext, Bullet::RADIUS,8U);
	m_collider       = std::make_unique<SphereCollider>(this, m_radius);

	m_sight           = std::make_unique<Sight>(this);
	m_wallApproach    = std::make_unique<WallApproach>(this);
	m_wallApproachVel = std::make_unique<WallApproach>(this);

	m_blink = std::make_unique<Blink>();
	
	m_defaultColor = m_color;
	m_blinkColor   = Colors::Gray;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Character::Update(const DX::StepTimer& timer)
{
	timer;
	m_isWallContact = false;
	m_previousPos = m_position;

	float elapsedTime = float(timer.GetElapsedSeconds());

	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, quaternion);


	m_position += m_velocity;
	m_velocity = Vector3::Zero;



	m_sight->Update(timer);
	m_wallApproach->Update(timer);
	m_wallApproachVel->Update(timer);

	

	if (m_isDamage)
	{
		m_blink->Initialize(0.16f);
		m_blink->Start();
		m_invincibleTime -= elapsedTime;

	}

	if (m_invincibleTime <= 0.0f)
	{
		m_isDamage = false;
		m_blink->Stop();
		m_invincibleTime = INVINCIBLE_TIME;
	}


	if (m_hp <= 0)
	{
		if (GetTag() == GameObject::ObjectTag::Player)
			ResultState::m_isPlayerWin = false;
		else
			ResultState::m_isPlayerWin = true;;
		Destroy(this);
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}

	m_blink->Update(timer);
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

	m_world = scalemat * r * rotMat * transMat;


	if(m_blink->GetState())			
		m_color = m_defaultColor;
	else
		m_color = m_blinkColor;

	m_model->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);


	Matrix world = rotMat * transMat;

	if(PlayState::m_isDebug)
	m_sphereCollider->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);

	m_sight->Render();
	m_wallApproach->Render();
	m_wallApproachVel->Render();
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">オブジェクト</param>
void Character::OnCollision(GameObject* object)
{
	object;
	if (object->GetTag() == GameObject::ObjectTag::Wall)
	{
		m_position = m_previousPos;
		m_velocity = Vector3::Zero;
		m_isWallContact = true;
	}

	if (object->GetTag() == GameObject::ObjectTag::Bullet)
	{
		if (object->GetCharaTag() != GetTag() && m_isDamage == false)
		{
			m_isDamage = true;
			
			m_hp -= 1;
		}
	}
}

/// <summary>
/// 発砲
/// </summary>
void Character::Shoot()
{
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3::UnitY, m_rotation.y);
	std::unique_ptr<Bullet> shell = std::make_unique<Bullet>(ObjectTag::Bullet, GetTag(), m_position, rot);
	shell->SetModel(m_bulletModel.get());
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(shell));
}
