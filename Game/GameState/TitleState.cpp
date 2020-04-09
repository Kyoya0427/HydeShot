//======================================================
// File Name	: TitleState.cpp
// Summary	: �^�C�g���X�e�C�g
//======================================================
#include "TitleState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>

#include <Game\GameState\GameStateManager.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleState::TitleState()
	:IGameState()
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
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PLAY_STATE);
	}
}

/// <summary>
/// �`��
/// </summary>
void TitleState::Render(const DX::StepTimer& timer)
{
	timer;
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();
}

/// <summary>
/// �I��
/// </summary>
void TitleState::Finalize()
{

}


