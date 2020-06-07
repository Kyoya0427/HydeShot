//======================================================
// File Name	: CharacterController.h
// Summary		: �v���C���[�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class Character;

class CharacterController
{
public:
	//�R���X�g���N
	CharacterController(Character* character);
	//�f�X�g���N�^
	~CharacterController();

public:
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;

protected:
	Character*     m_character;
	//�X�e�C�g�ύX�C���^�[�o��
	float m_shotInterval;

};