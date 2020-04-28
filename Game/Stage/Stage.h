//======================================================
// File Name	: Stage.h
// Summary	: ステージクラス
// Date		: 2019/11/28
// Author		: Takafumi Ban
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

	// ステージデータのリセット関数
	void ResetStageData();

private:


	// 登録されているタスク（プレイヤー、敵、パーツ）を全て削除する関数
	void DeleteAllObject();

	// 位置からステージのマップチップの位置に変換する関数
	void ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y);

private:
	//----- ゲームオブジェクトへのポインタ -----//
	Player* m_player;
	Enemy* m_enemy;
	// 床オブジェクトへのポインタ
	Floor* m_floors[STAGE_H][STAGE_W];
	//パーツオブジェクトへのポインター

	//----- モデルへのポインタ -----//
	// 床のモデル
	std::unique_ptr<DirectX::Model> m_floorModels[Floor::STATE_NUM];

	// ステージデータ
	StageData m_stageData;

	//プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_playerModel[Player::MODEL_TYPE_NUM];
	std::unique_ptr<DirectX::Model> m_enemy_Model[Enemy::MODEL_TYPE_NUM];

};
