//======================================================
// File Name	: Player.cpp
// Summary	: プレイヤークラス
//日付け
//作成者
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

#include <DirectXTK\Keyboard.h>

#include <Game\Stage\Stage.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 床との判定用の幅と高さ
const float Player::WIDTH = 0.2f;
const float Player::HEIGHT = 0.2f;



Player::Player(const ObjectTag tag)
	: CharacterController(tag)
	, m_models{ nullptr }
	
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateCone(deviceContext);

}

Player::~Player()
{

}


void Player::Initialize(int x, int y, Stage* stage)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
	m_stage = stage;

	
}


void Player::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	float speed = 0.2f;
	float rot = 0.1f;

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
	{
		Forward(-speed);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
	{
		Backward(speed);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
	{
		Leftward(-speed);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
	{
		Rightward(speed);
	}


	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		LeftTurn(rot);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		RightTurn(rot);
	}

	


}

void Player::Render(const DX::StepTimer& timer)
{
	timer;
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);

	if (!gameWindow || !m_models[ModelType::NORMAL] ) return;

	Matrix scalemat = Matrix::CreateScale(m_scale);	
	Matrix r = Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90.0f));
	Matrix rotMat = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ワールド行列を作成
	
	m_world = scalemat * r * rotMat * transMat;

	m_geometricPrimitive->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Red);


}

void Player::OnCollision(IGameObject* object)
{
	object;
}

void Player::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

float Player::SLerap(float start, float end, float t)
{
	float rate = (sinf(3.0f*DirectX::XM_PI / 2.0f + DirectX::XM_PI * t) + 1.0f) / 2.0f;
	return start + (end - start) * rate;
}







