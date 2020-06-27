//======================================================
// File Name	: RuleBased.h
// Summary		: �j���[�����l�b�g���[�N
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

class Character;

class RuleBased
{
public:
	RuleBased();
	~RuleBased();

public:
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys);
};

