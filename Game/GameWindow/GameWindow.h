//======================================================
// File Name	: GameWindow.h
// Summary	: ゲームウィンドウ
//======================================================
#pragma once
#include <Effects.h>

#include <DirectXTK\GeometricPrimitive.h>
#include <DirectXTK\Keyboard.h>
#include <DirectXTK\PrimitiveBatch.h>
#include <DirectXTK\VertexTypes.h>

#include <Game\GameObject\IGameObject.h>



class Camera;
class Bg;



class GameWindow : public IGameObject
{
public:
	enum DIR
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	// 描画順
	enum PRIORITY
	{
		BG,      // 背景
		OBJECT,	//床の上のオブジェクト
		STAGE   //ステージ
	};


	// ゲームステート
	enum STATE
	{
		STATE_START, // 開始
		STATE_GAME, // ゲーム中
		STATE_AGAIN, // 死んだので再チャレンジ
		STATE_NEXT, // 次のステージへ
		STATE_GAMEOVER, // ゲームオーバー
	};

	// ラウンド数
	static const int ROUND_MAX;
	static const int HIGH_SCORE;

	static const float DIR_ANGLE[];

	static const float GRAVITY;
	static const float FALL_SPEED;
	static const float FALL_DISTANCE;
	static const float FALL_ROTATE_SPEED;

public:
	// 画面サイズ
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;

public:
	// コンストラクタ
	GameWindow();
	~GameWindow();
	// 初期化関数
	void Initialize();

	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;

	//	Stage* GetStage() { return m_stage.get(); }
	Camera* GetCamera() { return m_camera.get(); }
private:
	DirectX::Keyboard::KeyboardStateTracker		 m_tracker;
	// カメラテスト用モデル
	std::unique_ptr <Camera>                      m_camera;
	std::unique_ptr<Bg>                           m_bg;

};
