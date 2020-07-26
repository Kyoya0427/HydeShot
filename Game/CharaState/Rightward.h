//======================================================
// File Name	: Rightward.h
// Summary		: �E�ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Rightward : public CharaState
{
public:
	//�R���X�g���N�^
	Rightward();
	//�f�X�g���N�^
	~Rightward();
public:
	//������
	void Initialize(Character* chara, CharacterController* controller) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;

private:
	Character*           m_chara;
	CharacterController* m_controller;

};