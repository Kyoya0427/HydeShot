//======================================================
// File Name	: CharacterController.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class Enemy;


class AIController : public  CharacterController
{
public:
	//コンストラク
	AIController(Enemy* enemy);
	//デストラクタ
	~AIController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;

public:
	static const float  MOVE_SPEED;
	static const float  ROT_SPEED;

private:
	Enemy*						    m_enemy;
	float m_interval;
	int m_state;
};