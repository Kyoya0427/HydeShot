//======================================================
// File Name	: GameWindow.cpp
// Summary	: ゲームウィンドウ
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameWindow.h"

#include <DirectXTK\WICTextureLoader.h>

#include <Game\Stage\Stage.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\UI\InfoWindow.h>


#include <Game\GameState\GameStateManager.h>

#include "Bg.h"

const float GameWindow::DIR_ANGLE[] =
{
	DirectX::XMConvertToRadians(45.0f * 0),
	DirectX::XMConvertToRadians(45.0f * 1),
	DirectX::XMConvertToRadians(45.0f * 2),
	DirectX::XMConvertToRadians(45.0f * 3),
	DirectX::XMConvertToRadians(45.0f * 4),
	DirectX::XMConvertToRadians(45.0f * 5),
	DirectX::XMConvertToRadians(45.0f * 6),
	DirectX::XMConvertToRadians(45.0f * 7),
};

const float GameWindow::GRAVITY = 9.8f;
const float GameWindow::FALL_SPEED = 8.0f;
const float GameWindow::FALL_DISTANCE = 10.0f;
const float GameWindow::FALL_ROTATE_SPEED = 180.0f;
// ラウンド数
const int GameWindow::ROUND_MAX = 3;
// ハイスコアの初期値（1000 点）
const int GameWindow::HIGH_SCORE = 1000;

GameWindow::GameWindow()
	: m_gameState(STATE_PARTS_SELECT)
	, m_round(0)
	
	
	, m_selectParts(POWERUP)
{
	SetDrawPrio(GameWindow::DRAW_TOP);
}

GameWindow::~GameWindow()
{
	if (m_bg != nullptr)
	{
		m_bg->Invalidate();
		m_bg = nullptr;
	}
}

void GameWindow::Initialize()
{
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());

	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_bg));

	m_stage = std::make_unique<Stage>();
	m_stage->Initialize(); 


	InitializeGame();


	
	
}



void GameWindow::Update(const DX::StepTimer& timer)
{
	auto kb = DirectX::Keyboard::Get().GetState();
	m_tracker.Update(kb);
	float elapsedTime = float(timer.GetElapsedSeconds());

	
	

	switch (m_gameState)
	{
	case STATE_PARTS_SELECT: // パーツ選択画面
							 // 画面が開くまで待つ
	
		break;
	case STATE_START: // 開始
					  // ゲームスタート
		
		break;
	case STATE_GAME: // ゲーム中
		m_gameState = PlayGame(elapsedTime);
		if (m_gameState != STATE_GAME)
		{
			
		}
		break;
	case STATE_AGAIN: // プレイヤーが死んだので再スタート
					  // 画面が真っ黒になるまで待つ
	
		break;
	case STATE_NEXT: // 次のステージへ
					 // 画面が真っ黒になるまで待つ
		
		break;
	case STATE_GAMEOVER: // ゲームオーバー
						 // 画面が真っ黒になるまで待つ
	
		break;
	}
}

void GameWindow::Render(const DX::StepTimer& timer)
{
	timer;

	
	
}

void GameWindow::OnCollision(IGameObject * object)
{
	object;
}

GameWindow::GAME_STATE GameWindow::InitializeGame()
{
	

	// ラウンド数を設定
	m_round = 1;

	

	// ステージデータの読み込み
	m_stage->LoadStageData(L"Resources\\StageData\\Stage01.csv");
	// ステージデータの設定
	m_stage->SetStageData();
// パーツ選択画面へ
	return STATE_PARTS_SELECT;

}



GameWindow::GAME_STATE GameWindow::PlayGame(float elapsedTime)
{
	elapsedTime;
	// プレイヤーの移動処理
	return STATE_GAME;
}




wchar_t * GameWindow::GetStageFilename(int round)
{
	static wchar_t fname[32];
	wsprintfW(fname, L"Resources\\StageData\\Stage01.csv", round);
	return fname;
}


