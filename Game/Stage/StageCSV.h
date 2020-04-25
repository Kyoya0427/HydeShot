#pragma once
class StageCSV
{
public:
	StageCSV();
	~StageCSV();

	// ステージの大きさ
	static const int STAGE_W = 10;
	static const int STAGE_H = 10;
	// ステージデータの構造体
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};
	// ステージデータ
	StageData m_stageData;
	// ステージデータの読み込み関数
	bool LoadStageData(wchar_t* fname);

};

