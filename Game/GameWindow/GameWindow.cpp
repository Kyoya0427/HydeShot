//======================================================
// File Name	: GameWindow.cpp
// Summary		: ゲームウィンドウ
// Date			: 2019/11/26
// Author		: Takafumi Ban
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
	, m_life(0)
	, m_getPowerupParts(0)
	, m_powerupParts(0)
	, m_usePowerupParts(0)
	, m_getJumpParts(0)
	, m_jumpParts(0)
	, m_useJumpParts(0)
	, m_selectParts(POWERUP)
	, m_selectPartsDisplayFlag(false)
	, m_highScore(HIGH_SCORE)
	, m_score(0)
	, m_highScoreUpdate(false)
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
	// エフェクトの作成
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(GameContext().Get<DX::DeviceResources>()->GetD3DDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	GameContext().Get<DX::DeviceResources>()->GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements, 
																				DirectX::VertexPositionColorTexture::InputElementCount,
																				shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	// ヒットエフェクト用テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\hit_effect.png", nullptr, m_hitEffectTexture.GetAddressOf());
	// ジャンプエフェクト用テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\jump_effect.png", nullptr, m_jumpEffectTexture.GetAddressOf());
	// 煙エフェクト用テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\smoke_effect.png", nullptr, m_smokeEffectTexture.GetAddressOf());
	// パーツ選択画面用のテクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\partsSelect.png", nullptr, m_partsSelectTexture.GetAddressOf());

	
}

void GameWindow::OnCollision(IGameObject * object)
{
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
		ActiveOff();
	
		break;
	case STATE_START: // 開始
					  // ゲームスタート
		m_gameState = StartGame(elapsedTime);
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
	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateTranslation(4.5f, 0.0f, 5.5f);

	if (m_selectPartsDisplayFlag)
	{
		// パーツ選択画面用の操作説明文の表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_partsSelectTexture.Get(), DirectX::SimpleMath::Vector2(288, 200));
	}
	
}

void GameWindow::GetPowerupParts()
{
	

}

void GameWindow::GetJumpParts()
{
	
}

void GameWindow::ResetPowerupParts()
{


}

void GameWindow::ResetJumpParts()
{
}

GameWindow::GAME_STATE GameWindow::InitializeGame()
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	// 得点を初期化
	SetScore(0);
	// ハイスコア更新フラグを落とす
	m_highScoreUpdate = false;
	// ハイスコア更新通知を３秒間に設定
	m_highScoreBlinkTime = 3.0f;
	// ラウンド数を設定
	m_round = 1;

	// 残機数を設定
	m_life = 3;
	// パワーアップパーツのリセット
	ResetPowerupParts();
	// ジャンプパーツのリセット
	ResetJumpParts();
	// ステージデータの読み込み
	m_stage->LoadStageData(GetStageFilename(m_round));
	// ステージデータの設定
	m_stage->SetStageData();
// パーツ選択画面へ
	return STATE_PARTS_SELECT;

}

GameWindow::GAME_STATE GameWindow::SelectParts(float elapsedTime)
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	// パーツを一つも所持していなければパーツ選択画面はスルー
	if (m_powerupParts == 0 && m_jumpParts == 0) return STATE_START;
	switch (m_selectParts)
	{
	case POWERUP: // パワーアップパーツ選択中
	
		// 左キーが押された
		if (m_tracker.IsKeyPressed(DirectX::Keyboard::Left))
		{
			if (m_usePowerupParts > 0)
			{
				m_usePowerupParts--;
			}
		}

		break;
	case JUMP: // ジャンプパーツ選択中
		// 左キーが押された
		if (m_tracker.IsKeyPressed(DirectX::Keyboard::Left))
		{
			if (m_useJumpParts > 0)
			{
				m_useJumpParts--;
			}
		}
		// スペースキーで次へ
		
		break;
	}
	return STATE_PARTS_SELECT;

}

GameWindow::GAME_STATE GameWindow::StartGame(float elapsedTime)
{

	// ゲーム中へ
	return STATE_GAME;
}

GameWindow::GAME_STATE GameWindow::PlayGame(float elapsedTime)
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	GAME_STATE state = STATE_GAME;
	// プレイヤーの移動処理
	return STATE_GAME;
}

void GameWindow::ActiveOff()
{
	
}

void GameWindow::SetScore(int score)
{
	

}

int GameWindow::GetScore()
{
	return m_score;
}

wchar_t * GameWindow::GetStageFilename(int round)
{
	static wchar_t fname[32];
	wsprintfW(fname, L"Resources\\StageData\\Stage01.csv", round);
	return fname;
}

bool GameWindow::CheckEnemyAllDead()
{
	
	return true;
}

void GameWindow::UpdateParts(bool stageClearFlag)
{
	

}
