
#include "PlayerController.h"

#include <Game\GameObject\Character.h>

#include <Game\Common\DebugFont.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayerController::MOVE_SPEED = 0.1f;
const float PlayerController::ROT_SPEED  = 0.1f;

PlayerController::PlayerController(Character* character)
	: CharacterController(character)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	m_shotInterval += float(timer.GetElapsedSeconds());

	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
	{
		m_character->Forward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
	{
		m_character->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
	{
		m_character->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
	{
		m_character->Rightward(MOVE_SPEED);
	}


	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		m_character->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		m_character->RightTurn(ROT_SPEED);
	}


	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Space) && m_shotInterval >= 0.1)
	{
		m_character->Shooting();
		m_shotInterval = 0.0f;
	}


}

void PlayerController::Render()
{
	
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 30, L"%f / 2.0", m_shotInterval);
	debugFont->draw();
}


