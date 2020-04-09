//======================================================
// File Name	: ResultState.cpp
// Summary	: リザルトステイト
//======================================================

#include "ResultState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>
/// <summary>
/// コンストラクタ
/// </summary>
ResultState::ResultState()
	:IGameState()

{
}

/// <summary>
/// デストラクタ
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
void ResultState::Initialize()
{

}

/// <summary>
/// デストラクタ
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void ResultState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}
}

/// <summary>
///描画
/// </summary>
void ResultState::Render(const DX::StepTimer& timer)
{
	timer;
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
}

/// <summary>
/// ファイナライズ
/// </summary>
void ResultState::Finalize()
{
}
