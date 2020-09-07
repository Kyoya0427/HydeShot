//======================================================
// File Name	: Leftward.h
// Summary		: ���ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Leftward : public CharaState
{
public:
	//�R���X�g���N�^
	Leftward();
	//�f�X�g���N�^
	~Leftward();

public:
	//������
	void Initialize(Character* chara, Character* enemy) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;

private:
	//�X�e�C�g���삷��L�����N�^�[
	Character*		m_chara;
	//�G�L�����N�^�[
	Character*		m_enemy;

};