//======================================================
// File Name	: AutoPlayerController.h
// Summary		: プレイヤーコントローラー
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/Search.h>

class AutoPlayerController : public  CharacterController
{
public:
	enum class InputID
	{
		NONE,

		FORWARD,
		BACKWARD,
		LEFTWARD,
		RIGHTWARD,
		LEFT_TURN,
		RIGHT_TURN,
		SHOOT
	};

public:
	//コンストラク
	AutoPlayerController(Character* character);
	//デストラクタ
	~AutoPlayerController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;

public:
	//データを取得
	void InitializeTraining(wchar_t* fname);

public:
	//移動速度
	static const float  MOVE_SPEED;
	//回転速度
	static const float  ROT_SPEED;
	//ショットインターバル
	static const float  SHOT_INTERVAL;
	//データの数
	static const int MAX_DATA = 1329;

private:
	//全ての計算データ
	std::vector<int>             m_data;
	//カウント
	int                          m_count;
	//データ保存するかどうか
	bool						 m_isSaveData;

};