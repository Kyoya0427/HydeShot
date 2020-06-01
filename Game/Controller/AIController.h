//======================================================
// File Name	: AIController.h
// Summary	: �`�h�R���g���[���[
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class AIController : public  CharacterController
{
public:
	enum  class Behavior
	{
		NONE,
		MOVE_FORWARD,	
		MOVE_BACKWARD,
		MOVE_LEFTWARD,
		MOVE_RIGHTWARD,		
		TURN_LEFT,
		TURN_RIGHT,
		SHOOT,

		NUM
	};

public:
	//�R���X�g���N
	AIController(Character* character);
	//�f�X�g���N�^
	~AIController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�f�o�b�N�`��
	void Render();

public:
	//�ړ����x
	static const float  MOVE_SPEED;
	//��]���x
	static const float  ROT_SPEED;

private:
	//�X�e�C�g�ύX�C���^�[�o��
	float m_interval;
	//�X�e�C�g
	Behavior m_state;
};