#include "pch.h"
#include "Enemy.h"
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>
#include <DirectXTK\CommonStates.h>
#include <Game\GameWindow\GameWindow.h>
#include <Game\Camera\Camera.h>

// 思考間隔（単位：秒）
const float Enemy::THINK_INTERVAL = 0.4f;

Enemy::Enemy(const ObjectTag tag)
	: IGameObject(tag)
	, m_models{nullptr}
{
}

void Enemy::Initialize(int x, int y)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);

	

}

void Enemy::Update(const DX::StepTimer & timer)
{
}


void Enemy::Render(const DX::StepTimer & timer)
{
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();


	if (!gameWindow || !m_models[NORMAL] ) return;

	

	// ワールド行列を作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
	m_models[NORMAL]->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());
}

void Enemy::OnCollision(IGameObject * object)
{
}

void Enemy::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

