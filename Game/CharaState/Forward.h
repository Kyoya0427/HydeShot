//======================================================
// File Name	: Forward.h
// Summary		: �O�ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Forward : public CharaState
{
public:
	//�R���X�g���N�^
	Forward();
	//�f�X�g���N�^
	~Forward();
public:
	//������
	void Initialize(Character* chara, Character* enemy) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;

private:
	//�X�e�C�g���삷��L�����N�^�[
	Character* m_chara;
	//�G�L�����N�^�[
	Character* m_enemy;

};