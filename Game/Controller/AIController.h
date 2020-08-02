//======================================================
// File Name	: AIController.h
// Summary		: �`�h�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <map>

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/WallAvoid.h>
#include <Game/CharaState/Search.h>

class RuleBased;
class NeuralNetworkManager;
class Ai;

class AIController : public  CharacterController
{
public:
	enum class AiType
	{
		RULEBASED,
		NEURALNETWORK,
	
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
	//�U���ɃX�e�C�g��ύX
	void ChangeAttackState();
	//�T�[�`�ɃX�e�C�g��ύX
	void ChangeSearchState();
	//�ǉ���ɃX�e�C�g��ύX
	void ChangeWallAvoidState();

public:
	using AiGroupList	  = std::map<AiType, std::unique_ptr<Ai>>;

public:
	//�ړ����x
	static const float  MOVE_SPEED;
	//��]���x
	static const float  ROT_SPEED;
	//�ő勗��
	static const float MAX_DISTANCE;
	//�V���b�g�C���^�[�o��
	static const float  SHOT_INTERVAL;
	//�X�e�[�g�C���^�[�o��
	static const float  STATE_INTERVAL;

	static const int    MODE_COUNT = 7;

private:
	//Ai�}�l�[�W���[
	AiGroupList                             m_aiManager;
	//�G�L����
	Character*                              m_enemy;
	//�X�e�C�g�ύX�C���^�[�o��
	float                                   m_stateInterval;

	CharaStateID                            m_state;
	//�U���X�e�[�g
	std::unique_ptr<Attack>                 m_attack;
	//�T�[�`�X�e�[�g
	std::unique_ptr<Search>                 m_search;
	//�ǉ���X�e�[�g
	std::unique_ptr<WallAvoid>              m_wallAvoid;
	
};