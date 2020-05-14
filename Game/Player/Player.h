//======================================================
// File Name	: Player.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Controller\CharacterController.h>

class Stage;

class Player : public CharacterController
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


	;

private:
	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// プレイヤーの状態
	STATE m_state;

	// ステージへのポインタ
	Stage* m_stage;
	
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;

	bool     m_isChoice;
public:
	// コンストラクタ
	Player(const ObjectTag tag);
	~Player();
	// 初期化関数
	void Initialize(int x, int y, Stage* stage);

public:
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer& timer) override;

	void OnCollision(IGameObject* object) override;

public:
	// モデル設定関数
	void SetModel(ModelType modelType, DirectX::Model* model);

	float SLerap(float start, float end, float t);

	

private:

};
