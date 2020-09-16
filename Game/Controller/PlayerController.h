//======================================================
// File Name	: PlayerController.h
// Summary		: �v���C���[�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/Search.h>

class PlayerController : public  CharacterController
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
	PlayerController(Character* character);
	//�f�X�g���N�^
	~PlayerController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;

public:
	// ���͂Əo�͂̒l���O���ɏo��
	void OutputDataFile(char* fname);

public:
	//�ړ����x
	static const float  MOVE_SPEED;
	//��]���x
	static const float  ROT_SPEED;
	//�V���b�g�C���^�[�o��
	static const float  SHOT_INTERVAL;

private:
	//�v�Z���̃f�[�^
	InputID					     m_data;
	//�S�Ă̌v�Z�f�[�^
	std::vector<InputID>         m_outputData;
	//�f�[�^�ۑ����邩�ǂ���
	bool						 m_isSaveData;
};