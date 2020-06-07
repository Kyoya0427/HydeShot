//======================================================
// File Name	: PlayerController.cpp
// Summary		: �v���C���[�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayerController.h"

#include <Game\GameObject\Character.h>

#include <Game\Common\DebugFont.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayerController::MOVE_SPEED = 0.1f;
const float PlayerController::ROT_SPEED  = 0.1f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="character">�R���g���[������I�u�W�F�N�g</param>
PlayerController::PlayerController(Character* character)
	: CharacterController(character)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::State keyState = Keyboard::Get().GetState();

	m_shotInterval += float(timer.GetElapsedSeconds());

	if (keyState.IsKeyDown(Keyboard::Keys::W))
	{
		m_character->Forward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::S))
	{
		m_character->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::A))
	{
		m_character->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::D))
	{
		m_character->Rightward(MOVE_SPEED);
	}

	if (keyState.IsKeyDown(Keyboard::Keys::Left))
	{
		m_character->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::Right))
	{
		m_character->RightTurn(ROT_SPEED);
	}

	if (keyState.IsKeyDown(Keyboard::Keys::Space) && m_shotInterval >= 0.1)
	{
		m_character->Shoot();
		m_shotInterval = 0.0f;
	}

}

/// <summary>
/// �f�o�b�N
/// </summary>
void PlayerController::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 30, L"%f / 2.0", m_shotInterval);
	debugFont->draw();
}


