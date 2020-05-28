//======================================================
// File Name	: CharacterController.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Controller\CharacterController.h>

class Player;

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
	static const float  MOVE_SPEED;
	static const float  ROT_SPEED;


};