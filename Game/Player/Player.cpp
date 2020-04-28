//======================================================
// File Name	: Player.cpp
// Summary		: プレイヤークラス
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#include "pch.h"
#include "Player.h"
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>
#include <DirectXTK\CommonStates.h>
#include <Game\GameWindow\GameWindow.h>
#include <Game\Camera\Camera.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>


// 床との判定用の幅と高さ
const float Player::WIDTH = 0.2f;
const float Player::HEIGHT = 0.2f;

// プレイヤーの最大移動速度
const float Player::MAX_SPEED =	0.1f;

Player::Player(const ObjectTag tag)
	: IGameObject(tag)
	,m_models{ nullptr }
	
{

}

Player::~Player()
{

}

float Player::SLerap(float start, float end, float t)
{
	float rate = (sinf(3.0f*DirectX::XM_PI / 2.0f + DirectX::XM_PI * t) + 1.0f) / 2.0f;
	return start + (end - start) * rate;
}
void Player::Initialize(int x, int y)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
	
}

void Player::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}



void Player::OnCollision(IGameObject * object)
{
}

void Player::Update(const DX::StepTimer& timer)
{
	
}

void Player::Render(const DX::StepTimer& timer)
{
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	

	if (!gameWindow || !m_models[NORMAL] ) return;



	

	// ワールド行列を作成
	DirectX::SimpleMath::Matrix world =  DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
	m_models[NORMAL]->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());
}



