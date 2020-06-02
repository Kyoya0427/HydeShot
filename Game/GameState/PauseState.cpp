//======================================================
// File Name	 : PauseState.cpp
// Summary	 : �|�[�Y�X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#include "PauseState.h"

#include <Game\GameState\GameStateManager.h>

#include <DirectXTK\Keyboard.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
PauseState::PauseState()
	:IGameState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PauseState::~PauseState()
{
}
/// <summary>
/// ������
/// </summary>
void PauseState::Initialize()
{
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PauseState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PopState();
	}
}
/// <summary>
/// �`��
/// </summary>
void PauseState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PauseState");
	debugFont->draw();
}
/// <summary>
/// �I��
/// </summary>
void PauseState::Finalize()
{
}
