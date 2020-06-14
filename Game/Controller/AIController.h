//======================================================
// File Name	: AIController.h
// Summary		: ＡＩコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class MoveModeSelection;

class AIController : public  CharacterController
{
public:
	enum  class Behavior
	{
		NONE,
		MOVE_FORWARD,	//1
		MOVE_BACKWARD,//2
		MOVE_LEFTWARD,//3
		MOVE_RIGHTWARD,	//4	
		TURN_LEFT,//5
		TURN_RIGHT,//6
		SHOOT,//7

		NUM
	};

public:
	//コンストラク
	AIController(Character* character);
	//デストラクタ
	~AIController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;
	//デバック描画
	void Render();

public:
	//移動速度
	static const float  MOVE_SPEED;
	//回転速度
	static const float  ROT_SPEED;
	//ショットインターバル
	static const float  SHOT_INTERVAL;
	static const float  STATE_INTERVAL;

private:
	std::unique_ptr<MoveModeSelection>   m_moveModeSelection;

	//ステイト変更インターバル
	float m_stateInterval;
	//ステイト
	Behavior m_state;
};