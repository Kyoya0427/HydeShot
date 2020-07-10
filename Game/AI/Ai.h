//======================================================
// File Name	: Ai.h
// Summary		: Ai�̊��N���X
// Date			: 2020/6/9
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

class Ai
{
public:
	//�R���X�g���N�^
	Ai() = default;
	//�f�X�g���N�^
	virtual ~Ai() = default;

public:
	//�s����I��
	virtual AIController::Behavior BehaviorSelection(Character* character, Character* enemys) = 0;
};