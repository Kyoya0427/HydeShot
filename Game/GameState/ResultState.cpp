//======================================================
// File Name	: ResultState.cpp
// Summary		: ���U���g�X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "ResultState.h"

#include <Game\GameState\GameStateManager.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultState::ResultState()
	:IGameState()

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
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::TITLE_STATE);
	}
}

/// <summary>
///�`��
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(100, 100, L"Z Key");
	debugFont->draw();
}

/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void ResultState::Finalize()
{
}
