//======================================================
// File Name	: TitleState.cpp
// Summary		: タイトルステイト
// Author		: Kyoya Sakamoto
//======================================================
#include"TitleState.h"

#include <Game/Common/GameContext.h>
#include <Game/Common/DebugFont.h>

#include <Game/Game.h>

#include <Game/GameState/GameStateManager.h>

#include <Game/Bg/TitleBg.h>

#include <Game/UI/Button.h>

extern void ExitGame();

/// <summary>
/// コンストラクタ
/// </summary>
TitleState::TitleState()
	: IGameState()
{
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\defaultButton.png", nullptr, m_defaultTexture.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\selectButton.png", nullptr, m_selectTexture.ReleaseAndGetAddressOf());
}

/// <summary>
/// デストラクタ
/// </summary>
TitleState::~TitleState()
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleState::Initialize()
{
	m_titleBg = std::make_unique<TitleBg>();
	m_titleBg->Initialize(DirectX::SimpleMath::Vector3(0.0F,0.0f,0.0f));

	m_playButton = std::make_unique<Button>();
	m_playButton->Initialize(DirectX::SimpleMath::Vector2(100.0f, 500.0f), L"      Play");
	m_playButton->SetDefaultTexture(m_defaultTexture.Get());
	m_playButton->SetSelectTexture(m_selectTexture.Get());
	m_playButton->SetSelect(true);
	m_selectButton = SelectButtton::PLAY;

	m_exitButton = std::make_unique<Button>();
	m_exitButton->Initialize(DirectX::SimpleMath::Vector2(800.0f, 500.0f), L"       Exit");
	m_exitButton->SetDefaultTexture(m_defaultTexture.Get());
	m_exitButton->SetSelectTexture(m_selectTexture.Get());
	m_exitButton->SetSelect(false);
}

/// <summary>
///　更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void TitleState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		switch (m_selectButton)
		{
		case SelectButtton::PLAY:
		{
			using State = GameStateManager::GameState;
			GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
			gameStateManager->RequestState(State::SELECT_STATE);
		}
			break;
		case SelectButtton::EXIT:
			ExitGame();
			break;
		}
	}
	

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Left))
	{
		m_playButton->SetSelect(true);
		m_exitButton->SetSelect(false);
		m_selectButton = SelectButtton::PLAY;
	}
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Right))
	{
		m_playButton->SetSelect(false);
		m_exitButton->SetSelect(true);
		m_selectButton = SelectButtton::EXIT;
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleState::Render()
{
	m_titleBg->Render();
	m_playButton->Render();
	m_exitButton->Render();
}

/// <summary>
/// 終了
/// </summary>
void TitleState::Finalize()
{
}