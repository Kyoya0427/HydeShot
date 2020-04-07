//======================================================
// File Name	: MyGame.cpp
// Summary	: マイゲーム
// Author		: Kyoya Sakamoto
//======================================================
#include "MyGame.h"

#include <Keyboard.h>
#include <Mouse.h>

#include <Framework\DeviceResources.h>

#include <Utils\GameContext.h>
#include <Utils\DebugFont.h>

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
	//ステイトマネジャー生成
	m_stateManager = std::make_unique<GameStateManager>();
	//ゲームステイト登録
	using StateID = GameStateManager::GameStateID;
	m_stateManager->RegisterState<TitleState> (StateID::TITLE_STATE);
	m_stateManager->RegisterState<PlayState>  (StateID::PLAY_STATE);
	m_stateManager->RegisterState<PauseState> (StateID::PAUSE_STATE);
	m_stateManager->RegisterState<ResultState>(StateID::RESULT_STATE);
	//初期ステイト設定
	m_stateManager->SetStartState(StateID::TITLE_STATE);
	//コンテキストに登録
	GameContext().Register<GameStateManager>(m_stateManager);

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());

}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void MyGame::Update(const DX::StepTimer & timer)
{
	//ステイト更新
	m_stateManager->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void MyGame::Render(const DX::StepTimer & timer)
{
	//ステイト描画
	m_stateManager->Render(timer);
}

/// <summary>
/// 終了
/// </summary>
void MyGame::Finalize()
{

}
