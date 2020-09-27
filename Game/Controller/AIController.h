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

#include <Game/GameObject/SelectMode.h>

class NeuralNetworkManager;

class AIController : public  CharacterController
{
public:
	enum class AiType
	{
		NEURALNETWORK,
	
		NUM
	};

public:
	//�R���X�g���N
	AIController(Character* character, Character* enemy, SelectMode mode);
	//�f�X�g���N�^
	~AIController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;

public:
	//�U���ɃX�e�C�g��ύX
	void ChangeAttackState()    { m_charaState = static_cast<CharaState*>(m_attack.get());}
	//�T�[�`�ɃX�e�C�g��ύX
	void ChangeSearchState()    { m_charaState = static_cast<CharaState*>(m_search.get()); }
	//�ǉ���ɃX�e�C�g��ύX
	void ChangeWallAvoidState() { m_charaState = static_cast<CharaState*>(m_wallAvoid.get()); }
	//���[�h��ݒ�
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
	//�G�L����
	Character*                              m_enemy;
	//�j���[�����l�b�g���[�N
	std::unique_ptr<NeuralNetworkManager>   m_neuralNetworkManager;
	//�X�e�C�g�ύX�C���^�[�o��
	float                                   m_stateInterval;
	//���݂̃X�e�C�g
	CharaStateID                            m_state;
	//�U���X�e�[�g
	std::unique_ptr<Attack>                 m_attack;
	//�T�[�`�X�e�[�g
	std::unique_ptr<Search>                 m_search;
	//�ǉ���X�e�[�g
	std::unique_ptr<WallAvoid>              m_wallAvoid;

};