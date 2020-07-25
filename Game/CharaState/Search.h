//======================================================
// File Name	: Search.h
// Summary		: �T�[�`�̃X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/CharaState/Standing.h>
#include <Game/CharaState/Forward.h>
#include <Game/CharaState/Backward.h>
#include <Game/CharaState/LeftTurn.h>
#include <Game/CharaState/RightTurn.h>

#include <Game/Controller/CharacterController.h>

class Search : public CharaState
{
public:
	//�R���X�g���N�^
	Search();
public:
	//������
	void Initialize(Character* chara, CharacterController* controller) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;

public:
	void ChangeStandingState();
	void ChangeForwardState();
	void ChangeBackwardState();
	void ChangeLeftTurnState();
	void ChangeRightTurnState();

private:
	Character*                    m_chara;
	CharacterController*          m_controller;
	CharaState*				      m_search;

	std::unique_ptr<Standing>     m_standing;
	std::unique_ptr<Forward>      m_forward;
	std::unique_ptr<Backward>     m_backward;
	std::unique_ptr<LeftTurn>     m_leftTurn;
	std::unique_ptr<RightTurn>    m_rightTurn;
};