//======================================================
// File Name	: Character.cpp
// Summary		: キャラクター
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

const int   Character::MAX_HP = 5;
const float Character::INVINCIBLE_TIME = 2.0f;
const float Character::RADIUS = 0.4f;
const float Character::SCALE = 0.5;

/// <summary>
/// コンストラク
/// </summary>
Character::Character(const ObjectTag tag)
	: GameObject(tag)
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
	, m_charaModel()
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
	int x, y;
	x = static_cast<int>(pos.x);
	y = static_cast<int>(pos.y);
	SetPosition(DirectX::SimpleMath::Vector3(static_cast<float>(x), 0.0f, static_cast<float>(y)));
	SetRadius(RADIUS);
	SetScale(GetScale() * SCALE);

	m_hp = MAX_HP;
	m_invincibleTime = INVINCIBLE_TIME;

	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();


	m_sphereCollider = DirectX::GeometricPrimitive::CreateSphere(deviceContext,1.0f,8U);
	m_bulletModel    = DirectX::GeometricPrimitive::CreateSphere(deviceContext, Bullet::RADIUS,8U);
	m_collider       = std::make_unique<SphereCollider>(this, GetRadius());

	m_sight           = std::make_unique<Sight>(this);
	m_wallApproach    = std::make_unique<WallApproach>(this);
	m_wallApproachVel = std::make_unique<WallApproach>(this);

	m_blink = std::make_unique<Blink>();
	
	m_defaultColor = GetColor();
	m_blinkColor   = DirectX::Colors::Gray;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Character::Update(const DX::StepTimer& timer)
{
	timer;
	m_isWallContact = false;
	m_previousPos = GetPosition();

	float elapsedTime = float(timer.GetElapsedSeconds());

	GameContext::Get<CollisionManager>()->Add(GetTag(), m_collider.get());
	DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetRotation().y);
	SetVelocity(DirectX::SimpleMath::Vector3::Transform(GetVelocity(), quaternion));
	SetPosition(GetPosition() + GetVelocity());
	SetVelocity(DirectX::SimpleMath::Vector3::Zero);

	m_sight->Update(timer);
	m_wallApproach->Update(timer);
	m_wallApproachVel->Update(timer);

	HpProcessing(elapsedTime);
	
	m_blink->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
void Character::Render()
{
	DirectX::SimpleMath::Quaternion rot  = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetRotation().y);
	DirectX::SimpleMath::Matrix scalemat = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	DirectX::SimpleMath::Matrix rotMat   = DirectX::SimpleMath::Matrix::CreateFromQuaternion(rot);
	DirectX::SimpleMath::Matrix transMat = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// ワールド行列を作成
	DirectX::SimpleMath::Matrix matrix = scalemat * rotMat * transMat;

	SetWorld(matrix);

	if (m_blink->GetState())
		m_charaModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
			               , *GameContext::Get<DirectX::CommonStates>()
			               , GetWorld()
			               , GameContext::Get<Camera>()->GetView()
			               , GameContext::Get<Camera>()->GetProjection(), false);
	
	
	DirectX::SimpleMath::Matrix world = rotMat * transMat;

	if(PlayState::m_isDebug)
	m_sphereCollider->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), GetColor(), nullptr, true);
	
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
		SetPosition(m_previousPos);
		SetVelocity(DirectX::SimpleMath::Vector3::Zero);
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
	DirectX::SimpleMath::Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetRotation().y);
	std::unique_ptr<Bullet> shell = std::make_unique<Bullet>(ObjectTag::Bullet, GetTag(), GetPosition(), rot);
	shell->SetModel(m_bulletModel.get());
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(shell));
}

/// <summary>
/// HP関連の処理
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void Character::HpProcessing(float elapsedTime)
{
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
			ResultState::m_isPlayerWin = true;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(GameStateManager::GameState::RESULT_STATE);
		Destroy(this);
		
	}
}
