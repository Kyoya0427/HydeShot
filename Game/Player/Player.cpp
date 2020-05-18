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
	: IGameObject(tag)
	, m_models{ nullptr }
	
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateCone(deviceContext);

}

Player::~Player()
{

}


void Player::Initialize(DirectX::SimpleMath::Vector2& pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
	m_position = DirectX::SimpleMath::Vector3((float)pos.x, 0.0f, (float)pos.y);

	
}


void Player::Update(const DX::StepTimer& timer)
{
	timer;
	m_position += m_velocity;
}

void Player::Render(const DX::StepTimer& timer)
{
	timer;
	
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);


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







