//======================================================
// File Name	: GameWindow.h
// Summary		: ゲームウィンドウ
// Date			: 2019/11/26
// Author		: Takafumi Ban
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

	// ヒットエフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hitEffectTexture;
	// ジャンプエフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumpEffectTexture;
	// 煙エフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_smokeEffectTexture;
	//----- エフェクト用 -----//
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_batchEffect;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// ゲームの状態
	GAME_STATE m_gameState;
	// ラウンド数
	int m_round;
	// 残機数
	int m_life;
	// 現在のステージで取得したパワーアップパーツ数
	int m_getPowerupParts;
	// 現在のステージで取得したジャンプパーツ数
	int m_getJumpParts;
	// パワーアップパーツ取得数
	int m_powerupParts;
	// 使用中パワーアップパーツ数
	int m_usePowerupParts;
	// ジャンプパーツ取得数
	int m_jumpParts;
	// 使用中ジャンプパーツ数
	int m_useJumpParts;
	// パーツ選択中の操作説明用の絵のテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_partsSelectTexture;
	// パーツ選択画面でどのパーツを選択中のパーツ
	SELECT_PARTS_KIND m_selectParts;
	// パーツ選択画面の説明文を表示するフラグ
	bool m_selectPartsDisplayFlag;
	// ハイスコア
	int m_highScore;
	// スコア
	int m_score;
	// ハイスコア更新フラグ
	bool m_highScoreUpdate;
	// ハイスコアの点滅時間
	float m_highScoreBlinkTime;

public:
	// パワーアップパーツを取得した時に呼び出す関数
	void GetPowerupParts();
	// ジャンプパーツを取得した時に呼び出す関数
	void GetJumpParts();
	// 現在所持しているパワーアップパーツ数を返す関数
	int GetPowerupPartsCnt() { return m_powerupParts; }
	// 現在所持しているジャンプパーツ数を返す関数
	int GetJumpPartsCnt() { return m_jumpParts; }
	// パワーアップパーツのリセット関数
	void ResetPowerupParts();
	// ジャンプパーツのリセット関数
	void ResetJumpParts();
	// ゲームの初期化関数
	GAME_STATE InitializeGame();
	// パーツ選択画面
	GAME_STATE SelectParts(float elapsedTime);
	// ゲームをスタートさせる関数
	GAME_STATE StartGame(float elapsedTime);
	// ゲーム中の関数
	GAME_STATE PlayGame(float elapsedTime);
	// 次のステージへ
	GAME_STATE NextGame(float elapsedTime);
	//パーツセレクト中動けないようにする
	void ActiveOff();
	// スコアを設定する関数
	void SetScore(int score);
	// スコアを取得する関数
	int GetScore();
	wchar_t *GetStageFilename(int round);
	bool CheckEnemyAllDead();
	void UpdateParts(bool stageClearFlag);

	// エフェクト用ベーシックエフェクトを取得する関数
	DirectX::BasicEffect* GetBatchEffect() { return m_batchEffect.get(); }
	// エフェクト用プリミティブバッチを取得する関数
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch() { return m_primitiveBatch.get(); }
	// エフェクト用入力レイアウトを取得する関数
	ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }
	// ヒットエフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetHitEffectTexture() { return m_hitEffectTexture.Get(); }
	// ジャンプエフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetJumpEffectTexture() { return m_jumpEffectTexture.Get(); }
	// 煙エフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetSmokeEffectTexture() { return m_smokeEffectTexture.Get(); }
};
