//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <memory>

#include <Model.h>

#include "IGameState.h"

class CollisionManager;
class PlayerManager;
class TPSCamera;
class StageManager;

class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;
	//終了
	void Finalize() override;

private:

	//当たり判定マネージャー
	std::unique_ptr<CollisionManager>   m_collisionManager;
	//ステージマネージャー
	std::unique_ptr<StageManager>       m_stageManager;
	//プレイヤーマネージャー
	std::unique_ptr<PlayerManager>      m_playerManager;
	//TPSカメラ
	std::unique_ptr<TPSCamera>          m_tpsCamera;


};

