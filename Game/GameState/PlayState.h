//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Common\StepTimer.h>

class GameWindow;
class InfoWindow;
class ObjectManager;
class Camera;
class Player;
class Enemy;
class Stage;
class Bg;

class PlayState 
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer);
	//描画
	void Render(const DX::StepTimer& timer);
	//終了
	void Finalize();

public: 
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;

private:
	// ゲーム画面のビューポート
	D3D11_VIEWPORT                          m_viewportGame;
	// 情報画面のビューポート
	D3D11_VIEWPORT                          m_viewportInfo;
	// 情報ウィンドウ
	std::unique_ptr<InfoWindow>             m_infoWindow;
	//Camera
	std::unique_ptr <Camera>                m_camera;
	//バックグラウンド
	std::unique_ptr<Bg>                     m_bg;
	//ステージ
	std::unique_ptr<Stage>					m_stage;
	//プレイイヤー
	std::unique_ptr<Player>                 m_player;
	//エネミー
	std::unique_ptr<Enemy>                  m_enemy;
	// ゲームオブジェクトマネージャー
	std::unique_ptr<ObjectManager>          m_objectManager;
};

