//======================================================
// File Name	: CharacterController.h
// Summary		: プレイヤークラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class Character;

class CharacterController
{
public:
	//コンストラク
	CharacterController(Character* character);
	//デストラクタ
	~CharacterController();

public:
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;

protected:
	Character*     m_character;
	//ステイト変更インターバル
	float m_shotInterval;

};