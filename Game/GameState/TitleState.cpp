//======================================================
// File Name	: TitleState.cpp
// Summary		: �^�C�g���X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include"TitleState.h"

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

#include <Game\GameState\GameStateManager.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleState::TitleState()
	: IGameState()
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
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::PLAY_STATE);
	}
}

/// <summary>
/// �`��
/// </summary>
void TitleState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();
	debugFont->print(100, 100, L"Z Key");
	debugFont->draw();
}

/// <summary>
/// �I��
/// </summary>
void TitleState::Finalize()
{
}

