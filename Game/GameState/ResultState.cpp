//======================================================
// File Name	: ResultState.cpp
// Summary		: リザルトステイト
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "ResultState.h"

#include <Game\GameState\GameStateManager.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

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
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::TITLE_STATE);
	}
}

/// <summary>
///描画
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(100, 100, L"Z Key");
	debugFont->draw();
}

/// <summary>
/// ファイナライズ
/// </summary>
void ResultState::Finalize()
{
}
