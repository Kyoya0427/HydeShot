//======================================================
// File Name	: TitleState.cpp
// Summary	: �^�C�g���X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================
#include <WICTextureLoader.h>
#include <Keyboard.h>

#include "TitleState.h"
#include "GameStateManager.h"

#include <Utils\GameContext.h>

#include <Framework\DeviceResources.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleState::TitleState()
	:IGameState()
	, m_blinkFlag(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleState::~TitleState()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void TitleState::Initialize()
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", NULL, m_texture.ReleaseAndGetAddressOf());
	m_pos = DirectX::SimpleMath::Vector2(0, 0);

	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\space.png", NULL, m_pushTexture.ReleaseAndGetAddressOf());
	m_pushPos = DirectX::SimpleMath::Vector2(430, 500);

	m_blink = std::make_unique<Blink>();
	m_blink->Initialize(0.16f);
	m_blink->Start();
}

/// <summary>
///�A�b�v�f�[�g 
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void TitleState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PLAY_STATE);
	}

	SelectPartsMode(true);
	m_blink->Update(timer);
}

/// <summary>
/// �`��
/// </summary>
void TitleState::Render(const DX::StepTimer& timer)
{
	timer;
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	if (m_blinkFlag == false || m_blink->GetState())
	{
		m_spriteBatch->Draw(m_pushTexture.Get(), m_pushPos);
	}
	m_spriteBatch->End();
}

/// <summary>
/// �I��
/// </summary>
void TitleState::Finalize()
{
}

void TitleState::SelectPartsMode(bool flag)
{
	m_blinkFlag = flag;
	// �_�ŊԊu�̐ݒ�
	if (m_blinkFlag == true)
	{
		m_blink->Initialize(0.2f);
	}
	else
	{
		m_blink->Initialize(0.2f);
	}
}
