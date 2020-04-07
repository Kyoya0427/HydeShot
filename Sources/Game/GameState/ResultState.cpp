//======================================================
// File Name	: ResultState.cpp
// Summary	: ���U���g�X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================

#include <WICTextureLoader.h>

#include "ResultState.h"
#include "GameStateManager.h"

#include <Utils\GameContext.h>
#include <Framework\DeviceResources.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultState::ResultState()
	:IGameState()
	, m_count(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void ResultState::Initialize()
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Result.png", NULL, m_texture.ReleaseAndGetAddressOf());
	m_pos = DirectX::SimpleMath::Vector2(0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void ResultState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}
}

/// <summary>
///�`��
/// </summary>
void ResultState::Render(const DX::StepTimer& timer)
{
	timer;
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	m_spriteBatch->End();
}

/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void ResultState::Finalize()
{
}
