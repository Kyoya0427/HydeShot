//======================================================
// File Name	: ResultState.cpp
// Summary		: ���U���g�X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "ResultState.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/GameState/GameStateManager.h>

#include <Game/Bg/ResultBg.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool  ResultState::m_isPlayerWin = true;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultState::ResultState()
	: IGameState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// ������
/// </summary>
void ResultState::Initialize()
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());

	m_resultBg = std::make_unique<ResultBg>();
	m_resultBg->Initialize(Vector3(0.0F, 0.0f, 0.0f));

	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\space.png", NULL, m_pushTexture.ReleaseAndGetAddressOf());
	m_pushPos = DirectX::SimpleMath::Vector2(430, 500);

	m_blink = std::make_unique<Blink>();
	m_blink->Initialize(0.16f);
	m_blink->Start();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void ResultState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::TITLE_STATE);
	}

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		m_isBlink = !m_isBlink;
	}

	m_blink->Update(timer);
}

/// <summary>
/// �`��
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, static_cast<Color>(Colors::White), 1.0f, L"ResultState");
	debugFont->draw();
	debugFont->print(100, 100, static_cast<Color>(Colors::White), 1.0f, L"Z Key");
	debugFont->draw();
	
	
	m_resultBg->Render();
	m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	if (m_isBlink == false || m_blink->GetState())
	{
		m_spriteBatch->Draw(m_pushTexture.Get(), m_pushPos);
	}

	m_spriteBatch->End();
}

/// <summary>
/// �I��
/// </summary>
void ResultState::Finalize()
{
}

