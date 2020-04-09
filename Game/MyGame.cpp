//======================================================
// File Name	: MyGame.cpp
// Summary	: マイゲーム
//======================================================
#include "MyGame.h"

#include <Game\Common\DeviceResources.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

#include <Game\GameState\GameStateManager.h>
#include <Game\GameState\TitleState.h>
#include <Game\GameState\PlayState.h>
#include <Game\GameState\PauseState.h>
#include <Game\GameState\ResultState.h>

/// <summary>
/// コンストラクタ
/// </summary>
MyGame::MyGame()
	: m_stateManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
MyGame::~MyGame()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();
}

/// <summary>
/// 初期化
/// </summary>
void MyGame::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	//ステイトマネジャー生成
	m_stateManager = std::make_unique<GameStateManager>();
	//ゲームステイト登録
	using StateID = GameStateManager::GameStateID;
	m_stateManager->RegisterState<TitleState>(StateID::TITLE_STATE);
	m_stateManager->RegisterState<PlayState>(StateID::PLAY_STATE);
	m_stateManager->RegisterState<PauseState>(StateID::PAUSE_STATE);
	m_stateManager->RegisterState<ResultState>(StateID::RESULT_STATE);
	//初期ステイト設定
	m_stateManager->SetStartState(StateID::TITLE_STATE);
	//コンテキストに登録
	GameContext().Register<GameStateManager>(m_stateManager);

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(deviceResources->GetD3DDevice(), deviceResources->GetD3DDeviceContext());

}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void MyGame::Update(const DX::StepTimer & timer)
{
	//ステイト更新
	m_stateManager->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer">タイマー</param>
void MyGame::Render(const DX::StepTimer & timer)
{
	//ステイト描画
	m_stateManager->Render(timer);
}

void MyGame::Finalize()
{
}
