//======================================================
// File Name	: MyGame.cpp
// Summary	: �}�C�Q�[��
//======================================================
#include "MyGame.h"

#include <Game\Common\DeviceResources.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

#include <Game\GameState\GameStateManager.h>
#include <Game\GameState\TitleState.h>
#include <Game\GameState\PlayState.h>
#include <Game\GameState\PauseState.h>
#include <Game\GameState\ResultState.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyGame::MyGame()
	: m_stateManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MyGame::~MyGame()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();
}

/// <summary>
/// ������
/// </summary>
void MyGame::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	//�X�e�C�g�}�l�W���[����
	m_stateManager = std::make_unique<GameStateManager>();
	//�Q�[���X�e�C�g�o�^
	using StateID = GameStateManager::GameStateID;
	m_stateManager->RegisterState<TitleState>(StateID::TITLE_STATE);
	m_stateManager->RegisterState<PlayState>(StateID::PLAY_STATE);
	m_stateManager->RegisterState<PauseState>(StateID::PAUSE_STATE);
	m_stateManager->RegisterState<ResultState>(StateID::RESULT_STATE);
	//�����X�e�C�g�ݒ�
	m_stateManager->SetStartState(StateID::TITLE_STATE);
	//�R���e�L�X�g�ɓo�^
	GameContext().Register<GameStateManager>(m_stateManager);

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(deviceResources->GetD3DDevice(), deviceResources->GetD3DDeviceContext());

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void MyGame::Update(const DX::StepTimer & timer)
{
	//�X�e�C�g�X�V
	m_stateManager->Update(timer);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void MyGame::Render(const DX::StepTimer & timer)
{
	//�X�e�C�g�`��
	m_stateManager->Render(timer);
}

void MyGame::Finalize()
{
}
