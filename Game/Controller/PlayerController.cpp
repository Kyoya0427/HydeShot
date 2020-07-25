//======================================================
// File Name	: PlayerController.cpp
// Summary		: プレイヤーコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayerController.h"

#include <Game/GameObject/Character.h>

#include <Game/Common/DebugFont.h>

#include <Game/GameState/PlayState.h>
using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayerController::MOVE_SPEED    = 0.05f;
const float PlayerController::ROT_SPEED     = 0.02f;
const float PlayerController::SHOT_INTERVAL = 0.3f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
PlayerController::PlayerController(Character* character)
	: CharacterController(character)
{
	m_shotInterval = SHOT_INTERVAL;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerController::~PlayerController()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::State keyState = Keyboard::Get().GetState();

	m_shotInterval -= float(timer.GetElapsedSeconds());
	
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

	if (keyState.IsKeyDown(Keyboard::Keys::Space) && m_shotInterval < 0.0f)
	{
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
	}


}

/// <summary>
/// 描画
/// </summary>
void PlayerController::Render()
{
	if (PlayState::m_isDebug)
	{
		


		
	}
}





