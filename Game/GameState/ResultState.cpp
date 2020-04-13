//======================================================
// File Name	: ResultState.cpp
// Summary	: リザルトステイト
//======================================================

#include "ResultState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>

using namespace DirectX;

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
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Z))
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
