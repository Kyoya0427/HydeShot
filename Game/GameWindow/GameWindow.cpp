//======================================================
// File Name	: GameWindow.cpp
// Summary	: �Q�[���E�B���h�E
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameWindow.h"

#include <DirectXTK\WICTextureLoader.h>

#include <Game\Stage\Stage.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\UI\InfoWindow.h>


#include <Game\GameState\GameStateManager.h>

#include "Bg.h"

const float GameWindow::DIR_ANGLE[] =
{
	DirectX::XMConvertToRadians(45.0f * 0),
	DirectX::XMConvertToRadians(45.0f * 1),
	DirectX::XMConvertToRadians(45.0f * 2),
	DirectX::XMConvertToRadians(45.0f * 3),
	DirectX::XMConvertToRadians(45.0f * 4),
	DirectX::XMConvertToRadians(45.0f * 5),
	DirectX::XMConvertToRadians(45.0f * 6),
	DirectX::XMConvertToRadians(45.0f * 7),
};

const float GameWindow::GRAVITY = 9.8f;
const float GameWindow::FALL_SPEED = 8.0f;
const float GameWindow::FALL_DISTANCE = 10.0f;
const float GameWindow::FALL_ROTATE_SPEED = 180.0f;
// ���E���h��
const int GameWindow::ROUND_MAX = 3;
// �n�C�X�R�A�̏����l�i1000 �_�j
const int GameWindow::HIGH_SCORE = 1000;

GameWindow::GameWindow()
	: m_gameState(STATE_PARTS_SELECT)
	, m_round(0)
	
	
	, m_selectParts(POWERUP)
{
	SetDrawPrio(GameWindow::DRAW_TOP);
}

GameWindow::~GameWindow()
{
	if (m_bg != nullptr)
	{
		m_bg->Invalidate();
		m_bg = nullptr;
	}
}

void GameWindow::Initialize()
{
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());

	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_bg));

	m_stage = std::make_unique<Stage>();
	m_stage->Initialize(); 


	InitializeGame();


	
	
}



void GameWindow::Update(const DX::StepTimer& timer)
{
	auto kb = DirectX::Keyboard::Get().GetState();
	m_tracker.Update(kb);
	float elapsedTime = float(timer.GetElapsedSeconds());

	
	

	switch (m_gameState)
	{
	case STATE_PARTS_SELECT: // �p�[�c�I�����
							 // ��ʂ��J���܂ő҂�
	
		break;
	case STATE_START: // �J�n
					  // �Q�[���X�^�[�g
		
		break;
	case STATE_GAME: // �Q�[����
		m_gameState = PlayGame(elapsedTime);
		if (m_gameState != STATE_GAME)
		{
			
		}
		break;
	case STATE_AGAIN: // �v���C���[�����񂾂̂ōăX�^�[�g
					  // ��ʂ��^�����ɂȂ�܂ő҂�
	
		break;
	case STATE_NEXT: // ���̃X�e�[�W��
					 // ��ʂ��^�����ɂȂ�܂ő҂�
		
		break;
	case STATE_GAMEOVER: // �Q�[���I�[�o�[
						 // ��ʂ��^�����ɂȂ�܂ő҂�
	
		break;
	}
}

void GameWindow::Render(const DX::StepTimer& timer)
{
	timer;

	
	
}

void GameWindow::OnCollision(IGameObject * object)
{
	object;
}

GameWindow::GAME_STATE GameWindow::InitializeGame()
{
	

	// ���E���h����ݒ�
	m_round = 1;

	

	// �X�e�[�W�f�[�^�̓ǂݍ���
	m_stage->LoadStageData(L"Resources\\StageData\\Stage01.csv");
	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();
// �p�[�c�I����ʂ�
	return STATE_PARTS_SELECT;

}



GameWindow::GAME_STATE GameWindow::PlayGame(float elapsedTime)
{
	elapsedTime;
	// �v���C���[�̈ړ�����
	return STATE_GAME;
}




wchar_t * GameWindow::GetStageFilename(int round)
{
	static wchar_t fname[32];
	wsprintfW(fname, L"Resources\\StageData\\Stage01.csv", round);
	return fname;
}


