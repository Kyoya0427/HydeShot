//======================================================
// File Name	: TitleState.cpp
// Summary	: タイトルステイト
//======================================================
#include "TitleState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>

/// <summary>
/// コンストラクタ
/// </summary>
TitleState::TitleState()
	:IGameState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleState::~TitleState()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
void TitleState::Initialize()
{
	
}

/// <summary>
///アップデート 
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void TitleState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PLAY_STATE);
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleState::Render(const DX::StepTimer& timer)
{
	timer;
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();
}

/// <summary>
/// 終了
/// </summary>
void TitleState::Finalize()
{

}


