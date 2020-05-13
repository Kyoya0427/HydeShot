//======================================================
// File Name	: GameWindow.h
// Summary	: ゲームウィンドウ
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

#include <DirectXTK\Keyboard.h>
#include <Game\Stage\Stage.h>
#include <Effects.h>
#include <DirectXTK\PrimitiveBatch.h>
#include <DirectXTK\VertexTypes.h>

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
	enum DRAW_PRIORITY
	{
		DRAW_TOP, // 一番手前（２Ⅾ表示やエフェクトで使用）
		DRAW_OBJECT, // 床の上のオブジェクト
		DRAW_SHADOW, // オブジェクトの影
		DRAW_STAGE, // ステージ
		DRAW_FALL, // 落下オブジェクト
		DRAW_BG, // 背景
	};

	
	// ゲームステート
	enum GAME_STATE
	{
		STATE_PARTS_SELECT, // パーツ選択画面
		STATE_START, // 開始
		STATE_GAME, // ゲーム中
		STATE_AGAIN, // 死んだので再チャレンジ
		STATE_NEXT, // 次のステージへ
		STATE_GAMEOVER, // ゲームオーバー
	};
	// パーツ選択画面用
	enum SELECT_PARTS_KIND
	{
		POWERUP, // パワーアップパーツ
		JUMP, // ジャンプパーツ
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


	Stage* GetStage() { return m_stage.get(); }
	Camera * GetCamera() { return m_camera.get(); }
private:
	DirectX::Keyboard::KeyboardStateTracker		 m_tracker;
	// カメラテスト用モデル
	std::unique_ptr <Camera>                      m_camera;
	std::unique_ptr<Bg>                           m_bg;
	std::unique_ptr<Stage>						  m_stage;


	//----- エフェクト用 -----//
	
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// ゲームの状態
	GAME_STATE m_gameState;
	// ラウンド数
	int m_round;
	
	
	// パーツ選択画面でどのパーツを選択中のパーツ
	SELECT_PARTS_KIND m_selectParts;
	

public:

	// ゲームの初期化関数
	GAME_STATE InitializeGame();

	// ゲーム中の関数
	GAME_STATE PlayGame(float elapsedTime);


	wchar_t *GetStageFilename(int round);


	
	// エフェクト用プリミティブバッチを取得する関数
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch() { return m_primitiveBatch.get(); }
	// エフェクト用入力レイアウトを取得する関数
	ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }

};
