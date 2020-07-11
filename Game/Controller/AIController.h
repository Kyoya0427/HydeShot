//======================================================
// File Name	: AIController.h
// Summary		: �`�h�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <map>

#include <Game/Controller/CharacterController.h>

class RuleBased;
class NeuralNetworkManager;
class Ai;

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
		SHOOT,			//5
		TURN_LEFT,		//6
		TURN_RIGHT,		//7

		NUM
	};

public:
	enum class AiType
	{
		RULEBASED,
		NEURALNETWORK,
	
		NUM
	};

public:


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
	using AiGroupList	  = std::map<AiType, std::unique_ptr<Ai>>;

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
	//Ai�}�l�[�W���[
	AiGroupList                             m_aiManager;
	//�X�e�C�g�ύX�C���^�[�o��
	float                                   m_stateInterval;
	//�X�e�C�g
	Behavior                                m_state;
	//�G�L����
	Character*                              m_enemy;
	//�����_�����[�h�Ɉڍs���邽�߂̃J�E���g
	int                                     m_randMobeCount;
};