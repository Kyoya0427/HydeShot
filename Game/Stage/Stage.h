//======================================================
// File Name	: Stage.h
// Summary	: ステージクラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>
#include "Floor.h"


#include <DirectXTK\Model.h>
#include <Game\Player\Player.h>
#include <Game\Enemy\Enemy.h>


class GameWindow;

class Stage
{
public:
	// オブジェクトＩＤ
	enum OBJECT_ID
	{
		NONE,			// なし
		PLAYER,			// プレイヤー
		ENEMY,		// 敵１
	};
	
	// ステージの大きさ
	static const int STAGE_W = 15;
	static const int STAGE_H = 15;

	// ステージデータの構造体
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};

public:
	// コンストラクタ
	Stage();
	// デストラクタ
	~Stage();

	// 初期化関数
	void Initialize();

	

	// 床タスク取得関数
	Floor* GetFloor(int x, int y);

	// ステージデータの読み込み関数
	bool LoadStageData(wchar_t* fname);

	// ステージデータ初期化関数
	void SetStageData();


	void SetPlayerPos(int x, int y);
	void SetEnemyPos(int x, int y);

	DirectX::SimpleMath::Vector2& GetPlayerPos();
	DirectX::SimpleMath::Vector2& GetEnemyPos();
private:
	//----- ゲームオブジェクトへのポインタ -----//
	Player* m_player;
	Enemy* m_enemy;

	DirectX::SimpleMath::Vector2  m_playerPos;

	DirectX::SimpleMath::Vector2  m_enemyPos;
	// 床オブジェクトへのポインタ
	Floor* m_floors[STAGE_H][STAGE_W];
	//パーツオブジェクトへのポインター

	//----- モデルへのポインタ -----//
	// 床のモデル
	std::unique_ptr<DirectX::Model> m_floorModels[Floor::STATE_NUM];



	//プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_playerModel[Player::MODEL_TYPE_NUM];
	std::unique_ptr<DirectX::Model> m_enemy_Model[Enemy::MODEL_TYPE_NUM];

public:
	// ステージデータ
	StageData m_stageData;
};
