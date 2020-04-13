//======================================================
// File Name	: GameWindow.h
// Summary	: �Q�[���E�B���h�E
//======================================================
#include "GameWindow.h"

#include <Game\Common\GameContext.h>

#include <Game\Camera\Camera.h>

#include <Game\GameWindow\Bg.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameWindow::GameWindow()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameWindow::~GameWindow()
{
	if (m_bg != nullptr)
	{
		m_bg->Invalidate();
		m_bg = nullptr;
	}
}

/// <summary>
/// ������
/// </summary>
void GameWindow::Initialize()
{
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext().Register<Camera>(m_camera.get());

	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void GameWindow::Update(const DX::StepTimer & timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void GameWindow::Render(const DX::StepTimer & timer)
{
	timer;
}
