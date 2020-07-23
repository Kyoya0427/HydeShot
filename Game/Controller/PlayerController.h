//======================================================
// File Name	: PlayerController.h
// Summary		: プレイヤーコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>



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
	//移動速度
	static const float  MOVE_SPEED;
	//回転速度
	static const float  ROT_SPEED;
	//ショットインターバル
	static const float  SHOT_INTERVAL;

public:



};