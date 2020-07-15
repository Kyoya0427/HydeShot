//======================================================
// File Name	: RuleBased.h
// Summary		: ���[���x�[�X
// Date			: 2020/6/27
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/AI/Ai.h>

class RuleBased : public Ai
{
public:
	//�R���X�g���N�^
	RuleBased();
	//�f�X�g���N�^
	virtual ~RuleBased();

public:
	//�s���p�^�[����I������
	AIController::Behavior BehaviorSelection(Character* character, Character* enemy) override;
	void Render() override;
};

