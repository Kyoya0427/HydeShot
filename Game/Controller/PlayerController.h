//======================================================
// File Name	: PlayerController.h
// Summary		: �v���C���[�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/Controller/CharacterController.h>



class PlayerController : public  CharacterController
{
public:
	//�R���X�g���N
	PlayerController(Character* character);
	//�f�X�g���N�^
	~PlayerController();

public:
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	void Render();

public:
	//�ړ����x
	static const float  MOVE_SPEED;
	//��]���x
	static const float  ROT_SPEED;
	//�V���b�g�C���^�[�o��
	static const float  SHOT_INTERVAL;

public:



};