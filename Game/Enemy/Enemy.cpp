//======================================================
// File Name	: Enemy.h
// Summary	: エネミー
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Enemy.h"

#include <DirectXTK\CommonStates.h>

#include <Game\Common\DebugFont.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>


#include <Game\Camera\Camera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 思考間隔（単位：秒）
const float Enemy::THINK_INTERVAL = 0.4f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag"></param>
Enemy::Enemy(const ObjectTag tag)
	: IGameObject(tag)
	, m_models{nullptr}
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateCone(deviceContext);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Enemy::Initialize(DirectX::SimpleMath::Vector2& pos)
{
	m_x = (int)pos.x;
	m_y = (int)pos.y;
//	m_position = DirectX::SimpleMath::Vector3((float)pos.x, 0.0f, (float)pos.y);
	m_position = DirectX::SimpleMath::Vector3(8.0f, 0.0f, 8.0f);

	
	m_state = 0;
	m_interval = 0.0f;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void Enemy::Update(const DX::StepTimer& timer)
{
	timer;
	m_position += m_velocity;
}


/// <summary>
///描画
/// </summary>
/// <param name="timer"></param>
void Enemy::Render(const DX::StepTimer & timer)
{
	timer;
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 30, L"%f / 2.0",m_interval);
	debugFont->draw();

	debugFont->print(10, 50, L"X = %f  Y = %f Z = %f", m_velocity.x, m_velocity.y, m_velocity.z);
	debugFont->draw();
	switch (m_state)
	{
	case FORWARD:
		debugFont->print(10, 10, L"FORWARD");
		debugFont->draw();
		break;
	case BACKWARD:
		debugFont->print(10, 10, L"BACKWARD");
		debugFont->draw();		break;
	case LEFTWARD:
		debugFont->print(10, 10, L"LEFTWARD");
		debugFont->draw();		break;
	case RIGHTWARD:
		debugFont->print(10, 10, L"RIGHTWARD");
		debugFont->draw();		break;
	case LEFT_TURN:
		debugFont->print(10, 10, L"LEFT_TURN");
		debugFont->draw();		break;
	case RIGHT_TURN:
		debugFont->print(10, 10, L"RIGHT_TURN");
		debugFont->draw();		break;
	}


	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);

	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix r = Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));
	Matrix rotMat = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ワールド行列を作成

	m_world = scalemat * r * rotMat * transMat;

	m_geometricPrimitive->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Blue);

}

/// <summary>
/// 衝突後の処理
/// </summary>
/// <param name="object"></param>
void Enemy::OnCollision(IGameObject * object)
{
	object;
}

/// <summary>
/// モデル設定
/// </summary>
/// <param name="modelType"></param>
/// <param name="model"></param>
void Enemy::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

void Enemy::SetState(int state)
{
	m_state = state;
}

void Enemy::SetInterval(float interval)
{
	m_interval = interval;
}

