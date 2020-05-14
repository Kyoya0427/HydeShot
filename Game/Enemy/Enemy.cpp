//======================================================
// File Name	: Enemy.h
// Summary	: �G�l�~�[
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Enemy.h"

#include <DirectXTK\CommonStates.h>

#include <Game\Common\DebugFont.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameWindow\GameWindow.h>

#include <Game\Camera\Camera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �v�l�Ԋu�i�P�ʁF�b�j
const float Enemy::THINK_INTERVAL = 0.4f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag"></param>
Enemy::Enemy(const ObjectTag tag)
	: CharacterController(tag)
	, m_models{nullptr}
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateCone(deviceContext);
}

/// <summary>
/// ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Enemy::Initialize(int x, int y)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);

	
	m_state = 0;
	m_interval = 0.0f;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void Enemy::Update(const DX::StepTimer & timer)
{
	timer;
	float speed = 0.01f;
	float rot = 0.01f;

	m_interval += float(timer.GetElapsedSeconds());
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (m_interval >= 2.0f)
	{
		m_interval = 0.0f;
		m_state = rand() % NUM;
	}

	switch (m_state)
	{
	case FORWARD:
		Forward(speed);
		break;
	case BACKWARD:
		Backward(-speed);
		break;
	case LEFTWARD:
		Leftward(speed);
		break;
	case RIGHTWARD:
		Rightward(-speed);
		break;
	case LEFT_TURN:
		LeftTurn(rot);
		break;
	case RIGHT_TURN:
		RightTurn(rot);
		break;
	}

	m_position += m_velocity;
}


/// <summary>
///�`��
/// </summary>
/// <param name="timer"></param>
void Enemy::Render(const DX::StepTimer & timer)
{
	timer;
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 30, L"%f / 2.0",m_interval);
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

	if (!gameWindow || !m_models[NORMAL] ) return;

	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);

	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix r = Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));
	Matrix rotMat = Matrix::CreateFromQuaternion(rot);
	Matrix transMat = Matrix::CreateTranslation(m_position);
	// ���[���h�s����쐬

	m_world = scalemat * r * rotMat * transMat;

	m_geometricPrimitive->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Red);

}

/// <summary>
/// �Փˌ�̏���
/// </summary>
/// <param name="object"></param>
void Enemy::OnCollision(IGameObject * object)
{
	object;
}

/// <summary>
/// ���f���ݒ�
/// </summary>
/// <param name="modelType"></param>
/// <param name="model"></param>
void Enemy::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

