//======================================================
// File Name	: RuleBased.h
// Summary		: ルールベース
// Date			: 2020/6/27
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

class Character;

class RuleBased
{
public:
	//コンストラクタ
	RuleBased();
	//デストラクタ
	~RuleBased();

public:
	//行動パターンを選択する
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys);
};

