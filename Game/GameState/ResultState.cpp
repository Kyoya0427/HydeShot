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

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool  ResultState::m_isPlayerWin = false;

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
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::TITLE_STATE);
	}
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

	if (m_isPlayerWin)
	{
		debugFont->print(500, 500, static_cast<Color>(Colors::White), 1.0f, L"Player Win");
		debugFont->draw();
	}
	else
	{
		debugFont->print(500, 500, static_cast<Color>(Colors::White), 1.0f, L"Enemy Win");
		debugFont->draw();
	}


}


/// <summary>
/// �I��
/// </summary>
void ResultState::Finalize()
{
}
