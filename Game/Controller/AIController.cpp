
#include "AIController.h"

#include <Game\Enemy\Enemy.h>

#include <Game\Controller\Character.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float AIController::MOVE_SPEED = 0.01f;
const float AIController::ROT_SPEED  = 0.1f;

/// <summary>
/// コンストラク
/// </summary>
AIController::AIController(Enemy* enemy)
{
	m_enemy = enemy;
	m_interval = 0.0f;
	m_state = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
AIController::~AIController()
{
}

void AIController::Update(const DX::StepTimer& timer)
{
	m_interval += float(timer.GetElapsedSeconds());
	m_enemy->SetInterval(m_interval);

	Vector3 vel = Vector3::Zero;
	Vector3 rot = m_enemy->GetRotation();

	m_enemy->SetVelocity(vel);

	if (m_interval >= 2.0f)
	{
		m_interval = 0.0f;
		m_state = rand() % Enemy::STATE::NUM;
	}

	switch (m_state)
	{
	case Enemy::STATE::FORWARD:
		m_enemy->SetState(m_state);
		m_character->Forward(vel, rot, MOVE_SPEED);
		break;
	case Enemy::STATE::BACKWARD:
		m_enemy->SetState(m_state);
		m_character->Backward(vel, rot, MOVE_SPEED);
		break;
	case Enemy::STATE::LEFTWARD:		
		m_enemy->SetState(m_state);
		m_character->Leftward(vel, rot, MOVE_SPEED);
		break;
	case Enemy::STATE::RIGHTWARD:
		m_enemy->SetState(m_state);
		m_character->Rightward(vel, rot, MOVE_SPEED);
		break;
	case Enemy::STATE::LEFT_TURN:
		m_enemy->SetState(m_state);
		m_character->LeftTurn(rot, ROT_SPEED);
		break;
	case Enemy::STATE::RIGHT_TURN:
		m_enemy->SetState(m_state);
		m_character->RightTurn(rot, ROT_SPEED);
		break;
	}

	m_enemy->SetVelocity(vel);
	m_enemy->SetRotation(rot);

}
