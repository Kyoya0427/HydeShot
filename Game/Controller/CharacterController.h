//======================================================
// File Name	: CharacterController.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class CharacterController : public IGameObject
{
public:
	//コンストラク
	CharacterController(const ObjectTag tag = ObjectTag::None);
	//デストラクタ
	~CharacterController();

public:
	//前進
	void Forward(float speed);
	//後進
	void Backward(float speed);
	//左に進む
	void Leftward(float speed);
	//右に進む
	void Rightward(float speed);
	//左に旋回
	void LeftTurn(float speed);
	//右に旋回
	void RightTurn(float speed);
};