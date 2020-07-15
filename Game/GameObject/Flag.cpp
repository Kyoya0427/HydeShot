//======================================================
// File Name	: Flag.cpp
// Summary		: 旗
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Flag.h"

#include <Game/GameObject/GameObject.h>
			  
#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
			  
#include <Game/Camera/Camera.h>
			  
#include <Game/Collider/CollisionManager.h>

#include <Game/GameState/GameStateManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag"></param>
Flag::Flag(const ObjectTag tag)
	: GameObject(tag)
	, m_model()
	, m_sphereCollider()
	, m_collider()
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
void Flag::Initialize(int x, int y)
{
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);

	m_radius = 0.4;
	if(GetTag() == ObjectTag::Flag_01)
	m_color = Colors::Red;
	if(GetTag() == ObjectTag::Flag_02)
	m_color = Colors::Blue;
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
	m_world = Matrix::CreateTranslation(m_position);

	m_model->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);
}

/// <summary>
/// 当たった後の判定
/// </summary>
/// <param name="object"></param>
void Flag::OnCollision(GameObject * object)
{
	object;
	Destroy(this);
	using State = GameStateManager::GameState;
	GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
	gameStateManager->RequestState(State::RESULT_STATE);
}
