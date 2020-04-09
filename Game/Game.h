//
// Game.h
//

#pragma once

#include <Game\Common\DeviceResources.h>
#include <Game\Common\StepTimer.h>

#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\CommonStates.h>
#include <DirectXTK\Keyboard.h>
#include <DirectXTK\Mouse.h>

#include <Game\MyGame.h>

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:
	static const wchar_t* WINDOW_TITLE;
	static const int      WINDOW_WIDTH;
	static const int      WINDOW_HEIGHT;

public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize(int& width, int& height) const;

private:

    void Update(const DX::StepTimer& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                               m_timer;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>       m_spriteBatch;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	    m_state;
	// マウス
	std::unique_ptr<DirectX::Mouse>			    m_mouse;
	//キーボード
	std::unique_ptr<DirectX::Keyboard>          m_keyboard;
	//マイゲーム
	std::unique_ptr<MyGame>                     m_myGame;
};
