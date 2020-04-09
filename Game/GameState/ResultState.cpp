//======================================================
// File Name	: ResultState.cpp
// Summary	: ���U���g�X�e�C�g
//======================================================

#include "ResultState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>
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

	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
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
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
}

/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void ResultState::Finalize()
{
}
