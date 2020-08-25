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

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool  ResultState::m_isPlayerWin = false;

/// <summary>
/// コンストラクタ
/// </summary>
ResultState::ResultState()
	: IGameState()
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// 初期化
/// </summary>
void ResultState::Initialize()
{
	
}

/// <summary>
/// 更新
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
/// 描画
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, static_cast<Color>(Colors::White), 1.0f, L"ResultState");
	debugFont->draw();
	debugFont->print(100, 100, static_cast<Color>(Colors::White), 1.0f, L"Z Key");
	debugFont->draw();

	if (m_isPlayerWin)
	{
		debugFont->print(500, 500, static_cast<Color>(Colors::White), 1.0f, L"Player Win");
		debugFont->draw();
	}
	else
	{
		debugFont->print(500, 500, static_cast<Color>(Colors::White), 1.0f, L"Enemy Win");
		debugFont->draw();
	}


}


/// <summary>
/// 終了
/// </summary>
void ResultState::Finalize()
{
}
