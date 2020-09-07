//======================================================
// File Name	: LeftTurn.h
// Summary		: 左回転ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class LeftTurn : public CharaState
{
public:
	//コンストラクタ
	LeftTurn();
	//デストラクタ
	~LeftTurn();

public:
	//初期化
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;

private:
	//ステイト操作するキャラクター
	Character*		m_chara;
	//敵キャラクター
	Character*		m_enemy;

};