//======================================================
// File Name	: RuleBased.h
// Summary		: ���[���x�[�X
// Date			: 2020/6/27
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

class Character;

class RuleBased
{
public:
	//�R���X�g���N�^
	RuleBased();
	//�f�X�g���N�^
	~RuleBased();

public:
	//�s���p�^�[����I������
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys);
};

