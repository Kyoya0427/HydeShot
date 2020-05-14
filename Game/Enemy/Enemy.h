//======================================================
// File Name	: Enemy.h
// Summary	: エネミー
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>


class Enemy : public CharacterController
{
public:
	// 敵のタイプ別モデル
	enum ModelType
	{
		NORMAL,	// 通常
		

		MODEL_TYPE_NUM
	};
	// 敵の状態
	enum STATE
	{
		FORWARD,	// 通常
		BACKWARD,
		LEFTWARD,
		RIGHTWARD,		// 死亡
		LEFT_TURN,
		RIGHT_TURN,
		NUM
	};
	
	// 思考間隔（単位：秒）
	static const float THINK_INTERVAL;

public: 
	Enemy(const ObjectTag tag);
	// 初期化
	void Initialize(int x, int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render(const DX::StepTimer & timer) override;
	//衝突後の処理
	void OnCollision(IGameObject* object) override;

public:
	// モデル設定
	void SetModel(ModelType modelType, DirectX::Model* model);
	
private:
	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];
	// プレイヤーの状態
	int m_state;
	float m_interval;

	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
};