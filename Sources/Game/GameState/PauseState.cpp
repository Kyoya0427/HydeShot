//======================================================
// File Name	 : PauseState.cpp
// Summary	 : ポーズステイト
// Author		 : Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "PauseState.h"
#include "GameStateManager.h"

#include <Keyboard.h>

#include <Utils\GameContext.h>


/// <summary>
/// コンストラクタ
/// </summary>
PauseState::PauseState()
	:IGameState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PauseState::~PauseState()
{
}
/// <summary>
/// 初期化
/// </summary>
void PauseState::Initialize()
{
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PauseState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PopState();
	}
}
/// <summary>
/// 描画
/// </summary>
void PauseState::Render(const DX::StepTimer& timer)
{
	timer;
}
/// <summary>
/// 終了
/// </summary>
void PauseState::Finalize()
{
}
