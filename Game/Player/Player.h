//======================================================
// File Name	: Player.h
// Summary		: プレイヤークラス
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class Stage;

class Player : public IGameObject
{
public:
	// プレイヤーのタイプ別モデル
	enum ModelType
	{
		NORMAL,	// 通常
		SELECTION_RANGE,
		CURSOR,

		MODEL_TYPE_NUM
	};

	// プレイヤーの状態
	enum STATE
	{
		STANDING,	// 通常
		MOVE,
		ATTACK,
		DEAD,		// 死亡
		NEXT
	};

	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;


	struct Map
	{
		int size;
		int map[9][9];
	};

	struct RangeMap
	{
		Map move;
		Map attack;
	};

private:
	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// プレイヤーの状態
	STATE m_state;

	// ステージへのポインタ
	Stage* m_stage;
	
	RangeMap m_rangeMap;

	DirectX::SimpleMath::Vector3 m_cursorPos;

	bool     m_isChoice;
public:
	// コンストラクタ
	Player(const ObjectTag tag);
	~Player();
	// 初期化関数
	void Initialize(int x, int y, Stage* stage);

	// モデル設定関数
	void SetModel(ModelType modelType, DirectX::Model* model);

	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;



	float SLerap(float start, float end, float t);

	void MoveRange(Map* map, int x, int y, int step_count);
	void AttackRange(Map* map, int x, int y, int range_count);
	void MovePhaseRender();
	void MoveCursor();

private:
	void GetMap(int x, int y, int size1, int size2);
};
