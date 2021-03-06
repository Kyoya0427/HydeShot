//======================================================
// File Name	 : PlayState.h
// Summary		 : プレイステイト
// Author		 : Kyoya  Sakamoto
//======================================================
#pragma once

#include <list>

#include <Game\GameState\IGameState.h>

#include <Game\Common\StepTimer.h>

#include <DirectXTK/Model.h>

class GameWindow;
class InfoWindow;
class ObjectManager;
class Camera;
class PlayerController;
class AIController;
class AutoPlayerController;
class Stage;
class Bg;
class Character;
class Collision;
class ArtilleryShell;
class CollisionManager;

class PlayState : public IGameState
{
private:
	enum Tank
	{
		RED,
		BLUE,

		NUM
	};
public:
	PlayState();
	 ~PlayState();

public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//終了
	void Finalize() override;

public:
	//当たり判定するオブジェクトタグを登録
	void RegisterTheObject();
	//キャラクターを登録
	void CreateCharacter();

	//デバック表記
	void Debug();

public: 
	//ゲーム画面横
	static const int SCREEN_W = 960;
	//ゲーム画面縦
	static const int SCREEN_H = 720;
	//情報画面横
	static const int WINDOW_W = 320;
	//AI同士の場合の強制処理
	static const float END_TIMER;
	//デバック表記
	static bool		 m_isDebug;

private:
	// ゲーム画面のビューポート
	D3D11_VIEWPORT                              m_viewportGame;
	// 情報画面のビューポート
	D3D11_VIEWPORT                              m_viewportInfo;
	// 情報ウィンドウ
	std::unique_ptr<InfoWindow>                 m_infoWindow;
	//Camera
	std::unique_ptr <Camera>                    m_camera;
	//バックグラウンド
	std::unique_ptr<Bg>                         m_bg;
	//ステージ
	std::unique_ptr<Stage>					    m_stage;
	//エネミー
	std::unique_ptr<Character>                  m_enemy[2];
	//プレイヤー
	std::unique_ptr<Character>                  m_player;
	//エネミーコントローラー
	std::unique_ptr<AIController>               m_aiController[2];
	//プレイヤーコントローラー
	std::unique_ptr<PlayerController>           m_playerControll;
	//オートプレイヤーコントローラー
	std::unique_ptr<AutoPlayerController>       m_autoPlayerController;
	// ゲームオブジェクトマネージャー
	std::unique_ptr<ObjectManager>              m_objectManager;
	//当たり判定マネージャー
	std::unique_ptr<CollisionManager>           m_collisionManager;
	//キートラッカー
	DirectX::Keyboard::KeyboardStateTracker		m_keyTracker;
	//キャラクターのモデル
	std::unique_ptr<DirectX::Model>		        m_tankModels[static_cast<int>(Tank::NUM)];
	//A.I同士のみ使用タイマー
	float                                       m_gameEndTimer;

};

