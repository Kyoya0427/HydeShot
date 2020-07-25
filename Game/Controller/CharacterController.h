//======================================================
// File Name	: CharacterController.h
// Summary		: �L�����N�^�[�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

#include <Game/CharaState/CharaState.h>


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
	//�L�������擾
	Character* GetCharacter();

public:
	//�U���ɃX�e�C�g��ύX
	void ChangeAttackState();
	//�T�[�`�ɃX�e�C�g��ύX
	void ChangeSearchState();
	//�ǉ���ɃX�e�C�g��ύX
	void ChangeWallAvoidState();

protected:
	//���삷��I�u�W�F�N�g
	Character*                   m_character;
	//���삷��I�u�W�F�N�g�̃X�e�C�g
	CharaState*                  m_charaState;

	//�X�e�C�g�ύX�C���^�[�o��
	float                        m_shotInterval;

};