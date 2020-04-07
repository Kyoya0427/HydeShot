//======================================================
// File Name	: Game.cpp
// Summary	: ゲーム
// Author		: Kyoya Sakamoto
//======================================================

#include "Game.h"

#include <random>

#include <Game\MyGame.h>

#include <Utils\GameContext.h>
#include <Utils\Projection.h>

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
Game::Game() noexcept(false)
{
	//デバイスリソーシーズ生成と登録
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	GameContext().Register<DX::DeviceResources>(m_deviceResources);
}

/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
	
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void Game::Initialize(HWND window, int width, int height)
{
	//ウィンドウ設定
    m_deviceResources->SetWindow(window, width, height);
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

	m_myGame = std::make_unique<MyGame>();
	m_myGame->Initialize();
	// TODO: デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例: 60FPS固定タイムステップ更新ロジックに対しては以下を呼び出す

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60.0);
	
}

#pragma region Frame Update
/// <summary>
/// ゲームループ
/// </summary>
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void Game::Update(DX::StepTimer const& timer)
{
	//エスケープキーで終了しる処理
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Escape))
	{
		ExitGame();
	}

	m_myGame->Update(timer);
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// 描画
/// </summary>
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

    // TODO:これより下に記入
    context;

	m_myGame->Render(m_timer);

    m_deviceResources->PIXEndEvent();

    // 新しいフレームを表示します。
    m_deviceResources->Present();
}

// バックバッファーをクリアするヘルパーメソッド
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // ビューをクリアします
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // ビューポートを設定します。
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージハンドラー
void Game::OnActivated()
{
    // TODO: ゲームはアクティブウィンドウになりつつあります。
}

void Game::OnDeactivated()
{
	// TODO: ゲームは背景ウィンドウになりつつあります。
}
void Game::OnSuspending()
{
    // TODO: ゲームの電源が一時停止（または最小化）されています。
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: ゲームの電源が再開されています（または最小化から復帰しています）。
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

    // TODO: ゲームウィンドウのサイズが変更されています。
}

// プロパティ
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: 目的のデフォルトのウィンドウサイズに変更します（最小サイズは320x200であることに注意してください）。
    width = 1280;
    height = 720;
}

void Game::ChangeFullscreen(BOOL flag)
{
	m_deviceResources->GetSwapChain()->SetFullscreenState(flag, NULL);
}
#pragma endregion

#pragma region Direct3D Resources
// これらは、デバイスに依存するリソースです。
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: ここでデバイス依存オブジェクトを初期化します（ウィンドウサイズに依存しません）。
    device;
}

// ウィンドウのSizeChangedイベントで変更されるすべてのメモリリソースを割り当てます。
void Game::CreateWindowSizeDependentResources()
{
    // TODO: ここでウィンドウサイズに依存するオブジェクトを初期化します。

	// ウインドウサイズからアスペクト比を算出する
	
	
}

void Game::OnDeviceLost()
{
    // TODO:ここにDirect3Dリソースのクリーンアップを追加します。
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
