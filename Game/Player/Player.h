//======================================================
// File Name	: Player.h
// Summary		: プレイヤークラス
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>



class Player : public IGameObject
{
public:
	// プレイヤーのタイプ別モデル
	enum ModelType
	{
		NORMAL,	// 通常
		WING,	// ウイング付き

		MODEL_TYPE_NUM
	};

	// プレイヤーの状態
	enum STATE
	{
		STATE_NORMAL,	// 通常
		STATE_JUMP,		// ジャンプ中
		STATE_HIT,		// 吹き飛ばされ状態
		STATE_FALL,		// 落下中
		STATE_DEAD,		// 死亡
	};

	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;

	// プレイヤーの最大移動速度
	static const float MAX_SPEED;

	// プレイヤーの重さ
	static const float WEIGHT;

	// 床に対する摩擦係数
	static const float FRICTION;

	// ジャンプしているフレーム数
	static const int JUMP_FRAME;
	// ジャンプの高さ
	static const float JUMP_HEIGHT;


private:
	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// プレイヤーの状態
	STATE m_state;

	// パワーアップ
	int m_powerupParts;

	// ジャンプパーツを装着しているか？
	bool m_jumpParts;

	// ジャンプカウンター
	int m_jumpCounter;
	// 落下時の回転
	float m_fallRotateAngle;

public:
	// コンストラクタ
	Player(const ObjectTag tag);
	~Player();
	// 初期化関数
	void Initialize(int x, int y);

	// モデル設定関数
	void SetModel(ModelType modelType, DirectX::Model* model);


	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;


	float SLerap(float start, float end, float t);
private:

};
