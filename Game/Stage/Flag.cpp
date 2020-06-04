//======================================================
// File Name	: Flag.h
// Summary	: 旗
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Flag.h"

#include <Game\GameObject\GameObject.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\Collider\CollisionManager.h>

#include <Game/GameState/GameStateManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag"></param>
Flag::Flag(const ObjectTag tag)
	: GameObject(tag)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Flag::~Flag()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">初期座標</param>
void Flag::Initialize(DirectX::SimpleMath::Vector2& pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
	m_position = Vector3((float)m_x, 0.0f, (float)m_y);
	m_radius = 0.4;
	m_color = Colors::Red;
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_model = GeometricPrimitive::CreateCube(deviceContext);

	m_collider = std::make_unique<SphereCollider>(this, m_radius);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void Flag::Update(const DX::StepTimer & timer)
{
	timer;
	GameContext().Get<CollisionManager>()->Add(GetTag(),m_collider.get());
}

/// <summary>
/// 描画
/// </summary>
void Flag::Render()
{
	Matrix world = Matrix::CreateTranslation(m_position);

	m_model->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// 当たった後の判定
/// </summary>
/// <param name="object"></param>
void Flag::HitContact(GameObject * object)
{
	object;
	Destroy(this);
	using StateID = GameStateManager::GameStateID;
	GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
	gameStateManager->RequestState(StateID::RESULT_STATE);
}
