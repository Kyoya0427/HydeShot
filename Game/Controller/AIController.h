//======================================================
// File Name	: AIController.h
// Summary	: ＡＩコントローラー
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class AIController : public  CharacterController
{
public:
	enum  class Behavior
	{
		NONE,
		MOVE_FORWARD,	
		MOVE_BACKWARD,
		MOVE_LEFTWARD,
		MOVE_RIGHTWARD,		
		TURN_LEFT,
		TURN_RIGHT,
		SHOOT,

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

private:
	//ステイト変更インターバル
	float m_interval;
	//ステイト
	Behavior m_state;
};