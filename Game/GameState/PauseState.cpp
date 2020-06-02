//======================================================
// File Name	 : PauseState.cpp
// Summary	 : ポーズステイト
// Author		 : Kyoya Sakamoto
//======================================================
#include "PauseState.h"

#include <Game\GameState\GameStateManager.h>

#include <DirectXTK\Keyboard.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

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
void PauseState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PauseState");
	debugFont->draw();
}
/// <summary>
/// 終了
/// </summary>
void PauseState::Finalize()
{
}
