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
		STATE_NORMAL, // 通常
		STATE_HIT, // 吹き飛ばされ状態
		STATE_FALL, // 落下中
		STATE_DEAD, // 死亡
	};
	
	// 思考間隔（単位：秒）
	static const float THINK_INTERVAL;

public: 
	Enemy(const ObjectTag tag);
	// 初期化関数
	void Initialize(int x, int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;

	


	// モデル設定関数
	void SetModel(ModelType modelType, DirectX::Model* model);
	
private:
	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];
	// プレイヤーの状態


};