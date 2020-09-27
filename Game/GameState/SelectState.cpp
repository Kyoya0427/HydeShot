//======================================================
// File Name	 : SelectState.cpp
// Summary		 : ポーズステイト
// Date			 : 2020/5/12
// Author		 : Kyoya Sakamoto
//======================================================
#include "SelectState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameState\GameStateManager.h>

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
	, m_menu()
{
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\defaultButton.png", NULL, m_defaultTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\selectButton.png", NULL, m_selectTexture.ReleaseAndGetAddressOf());
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
	m_selectBg = std::make_unique<SelectBg>();
	m_selectBg->Initialize(Vector3(0.0F, 0.0f, 0.0f));
	
	m_menu = Menu::BLUE;

	for (int i = 0; i < 4; i++)
	{
		m_blueButton[i] = std::make_unique<Button>();
		m_blueButton[i]->SetDefaultTexture(m_defaultTexture.Get());
		m_blueButton[i]->SetSelectTexture(m_selectTexture.Get());
		m_blueButton[i]->SetSelect(false);
	}
	m_blueButton[static_cast<int>(SelectMode::TRAINING_1)]->Initialize(Vector2(30.0f, 200.0f), L"  1");
	m_blueButton[static_cast<int>(SelectMode::TRAINING_10)]->Initialize(Vector2(30.0f, 300.0f), L" 10");
	m_blueButton[static_cast<int>(SelectMode::TRAINING_50)]->Initialize(Vector2(30.0f, 400.0f), L" 50");
	m_blueButton[static_cast<int>(SelectMode::TRAINING_100)]->Initialize(Vector2(30.0f, 500.0f), L"100");
	m_blueButton[0]->SetSelect(true);

	for (int i = 0; i < static_cast<int>(SelectCharacter::NUM); i++)
	{
		m_charaSelectButton[i] = std::make_unique<Button>();
		m_charaSelectButton[i]->SetDefaultTexture(m_defaultTexture.Get());
		m_charaSelectButton[i]->SetSelectTexture(m_selectTexture.Get());
		m_charaSelectButton[i]->SetSelect(false);
	}

	m_charaSelectButton[static_cast<int>(SelectCharacter::PLAYER)]->Initialize(Vector2(460.0f, 200.0f), L"Player");
	m_charaSelectButton[static_cast<int>(SelectCharacter::ENEMY)]->Initialize(Vector2(460.0f, 400.0f), L"Enemy");

	for (int i = 0; i < static_cast<int>(SelectMode::NUM); i++)
	{
		m_redButton[i] = std::make_unique<Button>();
		m_redButton[i]->SetDefaultTexture(m_defaultTexture.Get());
		m_redButton[i]->SetSelectTexture(m_selectTexture.Get());
		m_redButton[i]->SetSelect(false);
	}
	m_redButton[static_cast<int>(SelectMode::TRAINING_1)]->Initialize(Vector2(880.0f, 200.0f), L"  1");
	m_redButton[static_cast<int>(SelectMode::TRAINING_10)]->Initialize(Vector2(880.0f, 300.0f), L" 10");
	m_redButton[static_cast<int>(SelectMode::TRAINING_50)]->Initialize(Vector2(880.0f, 400.0f), L" 50");
	m_redButton[static_cast<int>(SelectMode::TRAINING_100)]->Initialize(Vector2(880.0f, 500.0f), L"100");
	m_redButton[static_cast<int>(SelectMode::MANUAL_PLAYER)]->Initialize(Vector2(880.0f, 200.0f), L"Manual");
	m_redButton[static_cast<int>(SelectMode::AUTO_PLAYER)]->Initialize(Vector2(880.0f, 400.0f), L"Auto");

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void SelectState::Update(const DX::StepTimer& timer)
{
	timer;

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Up))
	{
		switch (m_menu)
		{
		case SelectState::Menu::BLUE:
		{
			int temp = static_cast<int>(m_blueMode);
			temp--;
			if (temp < 0) temp = 0;
			m_blueMode = static_cast<SelectMode>(temp);
		}
		break;
		case SelectState::Menu::SELECT:
		{
			int temp = static_cast<int>(m_selectChara);
			temp--;
			if (temp < 0) temp = 0;
			m_selectChara = static_cast<SelectCharacter>(temp);
		}
			break;
		case SelectState::Menu::RED:
		{
			if (m_selectChara == SelectCharacter::PLAYER)
			{
				int temp = static_cast<int>(m_redMode);
				temp--;
				if (temp < 4) temp = 4;
				m_redMode = static_cast<SelectMode>(temp);
			}

			if (m_selectChara == SelectCharacter::ENEMY)
			{
				int temp = static_cast<int>(m_redMode);
				temp--;
				if (temp < 0) temp = 0;
				m_redMode = static_cast<SelectMode>(temp);
			}
		}
			break;
		default:
			break;
		}
	}


	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Down))
	{
		switch (m_menu)
		{
		case SelectState::Menu::BLUE:
		{
			int temp = static_cast<int>(m_blueMode);
			temp++;
			if (temp > 3) temp = 3;
			m_blueMode = static_cast<SelectMode>(temp);
		}
		break;
		case SelectState::Menu::SELECT:
		{
			int temp = static_cast<int>(m_selectChara);
			temp++;
			if (temp > 1) temp = 1;
			m_selectChara = static_cast<SelectCharacter>(temp);
		}
			break;
		case SelectState::Menu::RED:
		{
			if (m_selectChara == SelectCharacter::PLAYER)
			{
				int temp = static_cast<int>(m_redMode);
				temp++;
				if (temp > 5) temp = 5;
				m_redMode = static_cast<SelectMode>(temp);
			}

			if (m_selectChara == SelectCharacter::ENEMY)
			{
				int temp = static_cast<int>(m_redMode);
				temp++;
				if (temp > 3) temp = 3;
				m_redMode = static_cast<SelectMode>(temp);
			}
		}
			break;
		default:
			break;
		}
	}

	switch (m_menu)
	{
	case SelectState::Menu::BLUE:
	{
		for (int i = 0; i < 4; i++)
		{
			m_blueButton[i]->SetSelect(false);
		}
		m_blueButton[static_cast<int>(m_blueMode)]->SetSelect(true);
	}
	break;
	case SelectState::Menu::SELECT:
	{
		for (int i = 0; i < static_cast<int>(SelectCharacter::NUM); i++)
		{
			m_charaSelectButton[i]->SetSelect(false);
		}
		m_charaSelectButton[static_cast<int>(m_selectChara)]->SetSelect(true);
	}
	break;
	case SelectState::Menu::RED:
		for (int i = 0; i < static_cast<int>(SelectMode::NUM); i++)
		{
			m_redButton[i]->SetSelect(false);
		}
		m_redButton[static_cast<int>(m_redMode)]->SetSelect(true);
		break;
	default:
		break;
	}
	

	


	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		switch (m_menu)
		{
		case SelectState::Menu::BLUE:
			m_menu = Menu::SELECT;
			m_charaSelectButton[static_cast<int>(SelectCharacter::PLAYER)]->SetSelect(true);
			break;
		case SelectState::Menu::SELECT:
		{
			m_menu = Menu::RED;
			if (m_selectChara == SelectCharacter::PLAYER)
			{
				m_redButton[static_cast<int>(SelectMode::MANUAL_PLAYER)]->SetSelect(true);
				m_redMode = SelectMode::MANUAL_PLAYER;
			}

			if (m_selectChara == SelectCharacter::ENEMY)
				m_redButton[static_cast<int>(SelectMode::TRAINING_1)]->SetSelect(true);
		
		}
			break;
		case SelectState::Menu::RED:
		{
			using State = GameStateManager::GameState;
			GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
			gameStateManager->RequestState(State::PLAY_STATE);
		}
			break;
		default:
			break;
		}
	}

}

/// <summary>
/// 描画
/// </summary>
void SelectState::Render()
{
	m_selectBg->Render();
	for (int i = 0; i < 4; i++)
	{
		m_blueButton[i]->Render();
	}
	for (int i = 0; i < static_cast<int>(SelectCharacter::NUM); i++)
	{
		m_charaSelectButton[i]->Render();		
	}

	if (m_menu != Menu::BLUE)
	{
		if (m_selectChara == SelectCharacter::PLAYER)
		{
			m_redButton[static_cast<int>(SelectMode::MANUAL_PLAYER)]->Render();
			m_redButton[static_cast<int>(SelectMode::AUTO_PLAYER)]->Render();
		}

		if (m_selectChara == SelectCharacter::ENEMY)
		{
			m_redButton[static_cast<int>(SelectMode::TRAINING_1)]->Render();
			m_redButton[static_cast<int>(SelectMode::TRAINING_10)]->Render();
			m_redButton[static_cast<int>(SelectMode::TRAINING_50)]->Render();
			m_redButton[static_cast<int>(SelectMode::TRAINING_100)]->Render();
		}
	}
}

/// <summary>
/// 終了
/// </summary>
void SelectState::Finalize()
{
}
