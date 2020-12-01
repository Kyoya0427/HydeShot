//======================================================
// File Name	: AutoPlayerController.h
// Summary		: �v���C���[�R���g���[���[
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/Search.h>

class AutoPlayerController : public  CharacterController
{
public:
	enum class InputID
	{
		NONE,

		FORWARD,
		BACKWARD,
		LEFTWARD,
		RIGHTWARD,
		LEFT_TURN,
		RIGHT_TURN,
		SHOOT
	};

public:
	//�R���X�g���N
	AutoPlayerController(Character* character);
	//�f�X�g���N�^
	~AutoPlayerController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;

public:
	//�f�[�^���擾
	void InitializeTraining(wchar_t* fname);

public:
	//�ړ����x
	static const float  MOVE_SPEED;
	//��]���x
	static const float  ROT_SPEED;
	//�V���b�g�C���^�[�o��
	static const float  SHOT_INTERVAL;
	//�f�[�^�̐�
	static const int MAX_DATA = 1329;

private:
	//�S�Ă̌v�Z�f�[�^
	std::vector<int>             m_data;
	//�J�E���g
	int                          m_count;
	//�f�[�^�ۑ����邩�ǂ���
	bool						 m_isSaveData;

};