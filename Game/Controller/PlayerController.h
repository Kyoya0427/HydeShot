//======================================================
// File Name	: CharacterController.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class Player;

class PlayerController : public  CharacterController
{
public:
	//コンストラク
	PlayerController(Character* character);
	//デストラクタ
	~PlayerController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;
	void Render();

public:
	static const float  MOVE_SPEED;
	static const float  ROT_SPEED;


};