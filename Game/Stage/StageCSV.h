//======================================================
// File Name	: StageCSV.h
// Summary		: ステージロード
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

class StageCSV
{
public:
	StageCSV();
	~StageCSV();

public:
	// ステージデータの読み込み関数
	bool LoadStageData(wchar_t* fname);

public:
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
	// ステージデータ
	StageData m_stageData;
	
	

};

