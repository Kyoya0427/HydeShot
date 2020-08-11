//======================================================
// File Name	: Stage.h
// Summary		: ステージクラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <DirectXTK\Model.h>

#include <Game/GameObject/Floor.h>
#include <Game/GameObject/Wall.h>

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

public:
	//初期化
	void Initialize();
	//床タスク取得
	int GetFloor(int x, int y);
	//ステージデータの読み込み
	bool LoadStageData(wchar_t* fname);
	//ステージデータ初期化
	void SetStageData();
	//初期座標を取得
	const DirectX::SimpleMath::Vector2& GetPlayerPos() { return m_playerPos; }
	const DirectX::SimpleMath::Vector2& GetEnemyPos() { return m_enemyPos; }
	//初期座標を設定
	void SetPlayerPos(int x, int y) { m_playerPos = DirectX::SimpleMath::Vector2((float)x, (float)y);}
	void SetEnemyPos(int x, int y)  { m_enemyPos  = DirectX::SimpleMath::Vector2((float)x, (float)y);}

private:
	//床
	Floor*     m_floor;	
	//壁
	Wall*      m_wall;
	//プレイヤー初期座標
	DirectX::SimpleMath::Vector2  m_playerPos;
	//敵初期座標
	DirectX::SimpleMath::Vector2  m_enemyPos;
	// 床のモデル
	std::unique_ptr<DirectX::Model> m_floorModels[static_cast<int>(Map::NUM)];

public:
	//ステージデータ
	StageData m_stageData;
};
