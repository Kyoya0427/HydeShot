//======================================================
// File Name	: AIController.h
// Summary		: �`�h�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>

class NeuralNetworkManager;
class RuleBased;

class AIController : public  CharacterController
{
public:
	enum  class Behavior
	{
		NONE,
		MOVE_FORWARD,	//1
		MOVE_BACKWARD,	//2
		MOVE_LEFTWARD,	//3
		MOVE_RIGHTWARD,	//4	
		TURN_LEFT,		//5
		TURN_RIGHT,		//6
		SHOOT,			//7

		NUM
	};

public:
	//�R���X�g���N
	AIController(Character* character, Character* enemy);
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
	//�V���b�g�C���^�[�o��
	static const float  SHOT_INTERVAL;
	static const float  STATE_INTERVAL;
	static const int    MODE_COUNT = 7;

private:
	//�j���[�����l�b�g���[�N
	std::unique_ptr<NeuralNetworkManager>   m_neuralNetworkManager;
	//���[���x�[�X
	std::unique_ptr<RuleBased>				m_ruleBased;
	//�X�e�C�g�ύX�C���^�[�o��
	float                                   m_stateInterval;
	//�X�e�C�g
	Behavior                                m_state;
	//�G�L����
	Character*                              m_enemy;
	//�����_�����[�h�Ɉڍs���邽�߂̃J�E���g
	int                                     m_randMobeCount;
};