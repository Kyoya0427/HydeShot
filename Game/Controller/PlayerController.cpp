//======================================================
// File Name	: PlayerController.cpp
// Summary		: プレイヤーコントローラー
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayerController.h"

#include <Game/GameObject/Character.h>

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/GameState/PlayState.h>

#include <Game/UI/HpUi.h>

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
	SetShotInterval(SHOT_INTERVAL);
	m_isSaveData   = false;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerController::~PlayerController()
{
	if(m_isSaveData)
	OutputDataFile("Resources//CSV//InputKey.csv");
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	SetShotInterval(GetShotInterval() - static_cast<float>(timer.GetElapsedSeconds()));

	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
	{
		m_data = InputID::FORWARD;
		GetCharacter()->Forward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
	{
		m_data = InputID::BACKWARD;
		GetCharacter()->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
	{
		m_data = InputID::LEFTWARD;
		GetCharacter()->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
	{
		m_data = InputID::RIGHTWARD;
		GetCharacter()->Rightward(MOVE_SPEED);
	}
	
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		m_data = InputID::LEFT_TURN;
		GetCharacter()->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		m_data = InputID::RIGHT_TURN;
		GetCharacter()->RightTurn(ROT_SPEED);
	}
	
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Space) && GetShotInterval() < 0.0f)
	{
		m_data = InputID::SHOOT;
		GetCharacter()->Shoot();
		SetShotInterval(SHOT_INTERVAL);
	}
	else
	{
		m_data = InputID::NONE;
	}

	m_outputData.push_back(m_data);
	GameContext::Get<HpUi>()->SetPlayerHp(GetCharacter()->GetHp());

}

/// <summary>
/// 入力と出力の値を外部に出力
/// </summary>
/// <param name="fname">出力するためのファイル</param>
void PlayerController::OutputDataFile(char* fname)
{
	FILE* f;
	errno_t error;
	error = fopen_s(&f, fname, "w");

	for (auto& InputID : m_outputData)
	{
		fprintf(f,"%d \n",static_cast<int>(InputID));
	}
	fclose(f);
}
