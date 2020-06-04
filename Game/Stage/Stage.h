//======================================================
// File Name	: Stage.h
// Summary		: ステージクラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <DirectXTK\Model.h>

#include <Game/Stage/Floor.h>
#include <Game/Stage/Wall.h>
#include <Game/Stage/Flag.h>


class GameWindow;

class Stage
{
public:
	// オブジェクトＩＤ
	enum OBJECT_ID
	{
		NONE,			// なし
		PLAYER,			// プレイヤー
		ENEMY,			// 敵１
		FLAG_01,
		FLAG_02,
		WALL,
	};
	
	enum Map
	{
		NIX,
		NORMAL,
		OUTER_WALL,

		NUM
	};
	// ステージの大きさ
	static const int STAGE_W = 16;
	static const int STAGE_H = 16;

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
	int GetFloor(int x, int y);

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
	Floor* m_floor;
	Wall* m_wall;
	Flag* m_flag[2];

	DirectX::SimpleMath::Vector2  m_playerPos;

	DirectX::SimpleMath::Vector2  m_enemyPos;
	
	//パーツオブジェクトへのポインター

	//----- モデルへのポインタ -----//
	// 床のモデル
	std::unique_ptr<DirectX::Model> m_floorModels[Map::NUM];

public:
	// ステージデータ
	StageData m_stageData;
};
