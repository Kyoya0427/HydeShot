//======================================================
// File Name	 : PauseState.cpp
// Summary		 : ポーズステイト
// Date			 : 2020/5/12
// Author		 : Kyoya Sakamoto
//======================================================
#include "PauseState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

#include <Game\GameState\GameStateManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

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
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::TITLE_STATE);
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
	debugFont->print(10, 10, static_cast<Color>(Colors::White), 1.0f, L"PauseState");
	debugFont->draw();
}

/// <summary>
/// 終了
/// </summary>
void PauseState::Finalize()
{
}
