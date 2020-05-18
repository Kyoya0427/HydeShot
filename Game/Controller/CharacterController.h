//======================================================
// File Name	: CharacterController.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class Character;

class CharacterController
{
public:
	//�R���X�g���N
	CharacterController();
	//�f�X�g���N�^
	~CharacterController();
public:
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;

protected:

	Character*     m_character;

};