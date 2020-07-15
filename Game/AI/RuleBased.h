//======================================================
// File Name	: RuleBased.h
// Summary		: ルールベース
// Date			: 2020/6/27
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/AI/Ai.h>

class RuleBased : public Ai
{
public:
	//コンストラクタ
	RuleBased();
	//デストラクタ
	virtual ~RuleBased();

public:
	//行動パターンを選択する
	AIController::Behavior BehaviorSelection(Character* character, Character* enemy) override;
	void Render() override;
};

