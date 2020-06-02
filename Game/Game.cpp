//
// Game.cpp
//


#include "Game.h"

#include <Game\Common\DeviceResources.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DebugFont.h>

#include <Game\GameState\GameStateManager.h>
#include <Game\GameState\TitleState.h>
#include <Game\GameState\PlayState.h>
#include <Game\GameState\PauseState.h>
#include <Game\GameState\ResultState.h>

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;


const wchar_t* Game::WINDOW_TITLE  = L"TBSG";
const int      Game::WINDOW_WIDTH  = 1280;
const int      Game::WINDOW_HEIGHT = 720;


Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	GameContext().Register<DX::DeviceResources>(m_deviceResources);
}

Game::~Game()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	width; height;

    m_deviceResources->SetWindow(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	 
	// コモンステート作成
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
	GameContext().Register<DirectX::CommonStates>(m_state);

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
	//キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();
	//キーボードトラッカー作成
	m_keyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	GameContext().Register<DirectX::Keyboard::KeyboardStateTracker>(m_keyTracker);
	// コモンステート作成
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
	GameContext::Register<DirectX::CommonStates>(m_state);
	// スプライトバッチの作成
	m_spriteBatch = std::make_unique<SpriteBatch>(m_deviceResources->GetD3DDeviceContext());
	GameContext::Register<SpriteBatch>(m_spriteBatch);
	
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();

	//ステイトマネジャー生成
	m_gameStateManager = std::make_unique<GameStateManager>();
	//ゲームステイト登録
	using StateID = GameStateManager::GameStateID;
	m_gameStateManager->RegisterState<TitleState>(StateID::TITLE_STATE);
	m_gameStateManager->RegisterState<PlayState>(StateID::PLAY_STATE);
	m_gameStateManager->RegisterState<PauseState>(StateID::PAUSE_STATE);
	m_gameStateManager->RegisterState<ResultState>(StateID::RESULT_STATE);
	//初期ステイト設定
	m_gameStateManager->SetStartState(StateID::TITLE_STATE);
	//コンテキストに登録
	GameContext().Register<GameStateManager>(m_gameStateManager);
	

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(deviceResources->GetD3DDevice(), deviceResources->GetD3DDeviceContext());

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:

    m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60.0);
    
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(const DX::StepTimer& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	//キーボードの更新
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker->Update(keyState);

	//ゲームステイトの更新
	m_gameStateManager->Update(timer);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    m_deviceResources->PIXEndEvent();
	
	//ゲームステイト描画
	m_gameStateManager->Render();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();


}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width  = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
