//======================================================
// File Name	: Ai.h
// Summary		: Ai�̊��N���X
// Date			: 2020/6/9
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Controller/AIController.h>

#include <Game/CharaState/CharaStateID.h>

class Ai
{
public:
	//�R���X�g���N�^
	Ai() = default;
	//�f�X�g���N�^
	virtual ~Ai() = default;

public:
	//�s����I��
	virtual CharaStateID BehaviorSelection() = 0;
	virtual void Render() = 0;
};