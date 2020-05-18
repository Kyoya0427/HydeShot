
#include "PlayerController.h"

#include <Game\Player\Player.h>

#include <Game\Controller\Character.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayerController::MOVE_SPEED = 0.1f;
const float PlayerController::ROT_SPEED  = 0.1f;

PlayerController::PlayerController(Player* player)
{
	m_player = player;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	Vector3 vel = Vector3::Zero;
	Vector3 rot = m_player->GetRotation();

	m_player->SetVelocity(vel);


	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
	{
		m_character->Forward(vel, rot, MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
	{
		m_character->Backward(vel, rot, MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
	{
		m_character->Leftward(vel, rot, MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
	{
		m_character->Rightward(vel, rot, MOVE_SPEED);
	}


	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		m_character->LeftTurn(rot, ROT_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		m_character->RightTurn(rot, ROT_SPEED);
	}

	m_player->SetVelocity(vel);
	m_player->SetRotation(rot);
}


