//======================================================
// File Name	: Floor.h
// Summary		: 床クラス
// Date			: 2019/11/28
// Author		: Takafumi Ban
//======================================================
#pragma once


#include <Game\GameObject\IGameObject.h>
#include <DirectXTK\Model.h>

class Stage;

class Floor : public IGameObject
{
public:
	// 床の状態
	enum State
	{
		NONE,		// 床なし
		NORMAL,		// 通常
		

		STATE_NUM
	};

	// ダメージの移行時間
	static const float DAMEGE_DELAY_TIME;

private:
	// ステージへのポインタ
	Stage* m_stage;

	// モデルデータへのポインタ
	DirectX::Model* m_models[STATE_NUM];

	// 床の状態
	State m_state;

	// 位置
	DirectX::SimpleMath::Vector3 m_pos;

	// ダメージフラグ（１フレームに１回しかダメージが入らないようにするためのフラグ）
	bool m_damageFlag;

	// ダメージが入って次の状態に移行するまでのタイマー
	float m_damageTimer;

public:
	// コンストラクタ
	Floor();

	// 初期化関数
	void Initialize(Stage* stage, int x, int y);

	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;

	// モデル設定関数
	void SetModel(State state, DirectX::Model* model);

	// 床の状態を設定する関数
	void SetState(Floor::State state) { m_state = state; }

	// 床の状態を取得する関数
	Floor::State GetState() { return m_state; }

	// ダメージを与える関数
	void Damage();

	// リセット関数
	void Reset();
};
