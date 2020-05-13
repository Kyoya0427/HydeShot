//======================================================
// File Name	: Enemy.h
// Summary	: エネミー
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>


class Enemy : public IGameObject
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
		STANDING,	// 通常
		MOVE,
		ATTACK,
		DEAD,		// 死亡
		NEXT
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


};