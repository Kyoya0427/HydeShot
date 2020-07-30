//======================================================
// File Name	: Attack.h
// Summary		: 攻撃ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Attack : public CharaState
{
public:
	//コンストラクタ
	Attack();

public:
	//初期化
	void Initialize(Character* chara , Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

protected:
	Character* m_chara;

};