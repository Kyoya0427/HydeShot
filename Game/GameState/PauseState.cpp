//======================================================
// File Name	 : PauseState.cpp
// Summary	 : �|�[�Y�X�e�C�g
//======================================================
#include "PauseState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>

using namespace DirectX;

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
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PopState();
	}
}
/// <summary>
/// �`��
/// </summary>
void PauseState::Render(const DX::StepTimer& timer)
{
	timer;
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
