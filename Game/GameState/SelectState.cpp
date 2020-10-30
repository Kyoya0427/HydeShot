//======================================================
// File Name	 : SelectState.cpp
// Summary		 : セレクトステイト
// Date			 : 2020/5/12
// Author		 : Kyoya Sakamoto
//======================================================
#include "SelectState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameState\GameStateManager.h>

#include <Game/UI/Blink.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

SelectMode                                   SelectState::m_blueMode = SelectMode::TRAINING_1;
SelectState::SelectCharacter	     	     SelectState::m_selectChara = SelectState::SelectCharacter::PLAYER;
SelectMode                                   SelectState::m_redMode = SelectMode::TRAINING_1;

/// <summary>
/// コンストラクタ
/// </summary>
SelectState::SelectState()
	: IGameState()
{
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\defaultButton.png", nullptr, m_defaultTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\selectButton.png", nullptr, m_selectTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\red.png", nullptr, m_redTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\blue.png", nullptr, m_blueTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\redChara.png", nullptr, m_redCharaTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\blueChara.png", nullptr, m_blueCharaTexture.ReleaseAndGetAddressOf());
}


/// <summary>
/// デストラクタ
/// </summary>
SelectState::~SelectState()
{
}

/// <summary>
/// 初期化
/// </summary>
void SelectState::Initialize()
{
	m_blink = std::make_unique<Blink>();
	m_blink->Initialize(0.5f);

	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());

	m_isSelectMode = true;
	m_isRedSelect = true;
	m_selectBg = std::make_unique<SelectBg>();
	m_selectBg->Initialize(Vector3(0.0F, 0.0f, 0.0f));
	
	m_selectMode = std::make_unique<OptionList>();
	m_selectMode->SetTexture(m_defaultTexture.Get(), m_selectTexture.Get());
	m_selectMode->Add(Vector2(30.0f, 200.0f), L"   A.I VS A.I");
	m_selectMode->Add(Vector2(30.0f, 400.0f), L"Player VS A.I");

	m_currentOption = m_selectMode.get();

	m_redOption = std::make_unique<OptionList>();
	m_redOption->SetTexture(m_defaultTexture.Get(), m_selectTexture.Get());


	m_blueOption = std::make_unique<OptionList>();
	m_blueOption->SetTexture(m_defaultTexture.Get(), m_selectTexture.Get());
	m_blueOption->Add(Vector2(880.0f, 200.0f), L"       1");
	m_blueOption->Add(Vector2(880.0f, 300.0f), L"      10");
	m_blueOption->Add(Vector2(880.0f, 400.0f), L"      50");
	m_blueOption->Add(Vector2(880.0f, 500.0f), L"     100");

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void SelectState::Update(const DX::StepTimer& timer)
{
	m_blink->Update(timer);

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);

	ArrowKey();
	SpaceKey();
	
}

/// <summary>
/// 描画
/// </summary>
void SelectState::Render()
{
	m_selectBg->Render();
	m_selectMode->Render();

	if (!m_isSelectMode)
	{
		m_redOption->Render();
		m_blueOption->Render();

		Vector2 redPos = Vector2(490, 40);
		Vector2 bluePos = Vector2(890, 40);

		m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());

		if (m_blink->GetState() && m_isRedSelect)
			m_spriteBatch->Draw(m_redTexture.Get(), redPos);

		if (m_blink->GetState() && !m_isRedSelect)
			m_spriteBatch->Draw(m_blueTexture.Get(), bluePos);

		Vector2 redCharaPos = Vector2(650, 30);
		Vector2 blueCharaPos = Vector2(1050, 36);
		m_spriteBatch->Draw(m_redCharaTexture.Get(), redCharaPos);
		m_spriteBatch->Draw(m_blueCharaTexture.Get(), blueCharaPos);

		m_spriteBatch->End();
	}
}

/// <summary>
/// 終了
/// </summary>
void SelectState::Finalize()
{
}

/// <summary>
/// 赤のモードリストに追加
/// </summary>
void SelectState::AddRedMode()
{
	switch (m_selectMode->GetCurrent())
	{
	case 0:
		m_redOption->Add(Vector2(460.0f, 200.0f), L"       1");
		m_redOption->Add(Vector2(460.0f, 300.0f), L"      10");
		m_redOption->Add(Vector2(460.0f, 400.0f), L"      50");
		m_redOption->Add(Vector2(460.0f, 500.0f), L"     100");
		break;
	case 1:
		m_redOption->Add(Vector2(460.0f, 200.0f), L"    Manual");
		m_redOption->Add(Vector2(460.0f, 400.0f), L"      Auto");
		break;
	}
}

/// <summary>
/// やじるしキー
/// </summary>
void SelectState::ArrowKey()
{
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Up))
	{
		m_currentOption->CurrentUp();
	}

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Down))
	{
		m_currentOption->CurrentDown();
	}

	if (!m_isSelectMode)
	{
		if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Left))
		{
			ChangeRedMode();
			m_isRedSelect = true;
		}
		if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Right))
		{
			ChangeBlueMode();
			m_isRedSelect = false;
		}
	}
}

/// <summary>
/// スペースキー
/// </summary>
void SelectState::SpaceKey()
{
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		if (m_isSelectMode)
		{
			m_isSelectMode = false;
			m_blink->Start();
			AddRedMode();
			ChangeRedMode();
		}
		else
		{
			m_selectChara = static_cast<SelectCharacter>(m_selectMode->GetCurrent());
			m_redMode = static_cast<SelectMode>(m_selectMode->GetCurrent() * 4 + m_redOption->GetCurrent());
			m_blueMode = static_cast<SelectMode>(m_blueOption->GetCurrent());

			using State = GameStateManager::GameState;
			GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
			gameStateManager->RequestState(State::PLAY_STATE);
		}
	}
}
