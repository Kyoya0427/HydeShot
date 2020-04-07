//======================================================
// File Name	:Game.h
// Summary	: ゲーム
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SpriteBatch.h>
#include <CommonStates.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "StepTimer.h"

class MyGame;

// ゲームループを提供するゲームクラス
class Game : public DX::IDeviceNotify
{
public:
	//コンストラクタ
    Game() noexcept(false);
	//デストラクタ
	~Game();
public:
    //初期化
    void Initialize(HWND window, int width, int height);

    //ゲームループ
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    //メッセージ
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    //プロパティ
    void GetDefaultSize( int& width, int& height ) const;
	void ChangeFullscreen(BOOL flag);

private:
	//更新
    void Update(DX::StepTimer const& timer);
    //描画
	void Render();
	//画面をクリアする
    void Clear();
	//デバイスを生成
    void CreateDeviceDependentResources();
	//ウィンドウ
    void CreateWindowSizeDependentResources();

    //デバイスリソーシーズ
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;
	//タイマー
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