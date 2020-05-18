//======================================================
// File Name	: CharacterController.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class Enemy;


class AIController : public  CharacterController
{
public:
	//�R���X�g���N
	AIController(Enemy* enemy);
	//�f�X�g���N�^
	~AIController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;

public:
	static const float  MOVE_SPEED;
	static const float  ROT_SPEED;

private:
	Enemy*						    m_enemy;
	float m_interval;
	int m_state;
};