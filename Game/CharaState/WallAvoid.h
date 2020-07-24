//======================================================
// File Name	: WallAvoid.h
// Summary		: �ǉ���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class WallAvoid : public CharaState
{
public:
	//�R���X�g���N�^
	WallAvoid();

public:
	//������
	void Initialize(Character* chara, CharacterController* controller) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;

protected:
	Character* m_chara;

};