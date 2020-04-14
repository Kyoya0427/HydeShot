//======================================================
// File Name	: GameWindow.h
// Summary	: ゲームウィンドウ
//======================================================
#include "GameWindow.h"

#include <Game\Common\GameContext.h>

#include <Game\Camera\Camera.h>

#include <Game\GameWindow\Bg.h>

/// <summary>
/// コンストラクタ
/// </summary>
GameWindow::GameWindow()
{
}

/// <summary>
/// デストラクタ
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
/// 初期化
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
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void GameWindow::Update(const DX::StepTimer & timer)
{
	timer;
	m_bg->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer">タイマー</param>
void GameWindow::Render(const DX::StepTimer & timer)
{
	timer;
	m_bg->Render(timer);
}

void GameWindow::OnCollision(IGameObject * object)
{
	object;
}
