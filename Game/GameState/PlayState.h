//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <list>

#include <Game\Common\StepTimer.h>

class GameWindow;
class InfoWindow;
class ObjectManager;
class Camera;
class PlayerController;
class AIController;
class Stage;
class Bg;
class Character;
class Collision;
class ArtilleryShell;
class CollisionManager;

class PlayState 
{
public:
	PlayState();
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
	std::unique_ptr<Character>              m_player;
	//プレイイヤーコントローラー
	std::unique_ptr<PlayerController>       m_playerController;
	//エネミー
	std::unique_ptr<Character>              m_enemy;
	//エネミーコントローラー
	std::unique_ptr<AIController>           m_aiController;
	// ゲームオブジェクトマネージャー
	std::unique_ptr<ObjectManager>          m_objectManager;
	//当たり判定マネージャー
	std::unique_ptr<CollisionManager>       m_collisionManager;
};

