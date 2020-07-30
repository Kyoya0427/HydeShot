//======================================================
// File Name	: Attack.h
// Summary		: �U���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Attack : public CharaState
{
public:
	//�R���X�g���N�^
	Attack();

public:
	//������
	void Initialize(Character* chara , Character* enemy) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;

protected:
	Character* m_chara;

};