//======================================================
// File Name	: PlayerController.h
// Summary		: プレイヤーコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/Search.h>

class PlayerController : public  CharacterController
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
	PlayerController(Character* character);
	//デストラクタ
	~PlayerController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;

public:
	// 入力と出力の値を外部に出力
	void OutputDataFile(char* fname);

public:
	//移動速度
	static const float  MOVE_SPEED;
	//回転速度
	static const float  ROT_SPEED;
	//ショットインターバル
	static const float  SHOT_INTERVAL;

private:
	//計算時のデータ
	InputID					     m_data;
	//全ての計算データ
	std::vector<InputID>         m_outputData;
	//データ保存するかどうか
	bool						 m_isSaveData;
};