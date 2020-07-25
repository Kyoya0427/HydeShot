//======================================================
// File Name	: RightTurn.h
// Summary		: 右回転ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class RightTurn : public CharaState
{
public:
	//コンストラクタ
	RightTurn();
	//デストラクタ
	~RightTurn();
public:
	//初期化
	void Initialize(Character* chara, CharacterController* controller) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

private:
	Character*           m_chara;
	CharacterController* m_controller;

};