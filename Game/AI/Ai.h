//======================================================
// File Name	: Ai.h
// Summary		: Aiの基底クラス
// Date			: 2020/6/9
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

class Ai
{
public:
	//コンストラクタ
	Ai() = default;
	//デストラクタ
	virtual ~Ai() = default;

public:
	//行動を選択
	virtual AIController::Behavior BehaviorSelection(Character* character, Character* enemys) = 0;
};