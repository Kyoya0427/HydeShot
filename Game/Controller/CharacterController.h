//======================================================
// File Name	: CharacterController.h
// Summary		: �L�����N�^�[�R���g���[���[
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
	

public:
	Character* GetCharacter() { return m_character; }
	CharaState* GetCharaState() { return m_charaState; }
	float GetShotInterval() { return m_shotInterval; }

public:
	void SetCharacter(Character* character) { m_character = character; }
	void SetCharaState(CharaState* charaState) { m_charaState = charaState; }
	void SetShotInterval(float shotInterval) { m_shotInterval = shotInterval; }

private:
	//���삷��I�u�W�F�N�g
	Character*                   m_character;
	//���삷��I�u�W�F�N�g�̃X�e�C�g
	CharaState*                  m_charaState;

	//�X�e�C�g�ύX�C���^�[�o��
	float                        m_shotInterval;

};