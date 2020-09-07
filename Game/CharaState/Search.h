//======================================================
// File Name	: Search.h
// Summary		: �T�[�`�̃X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

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
	//�f�X�g���N�^
	~Search();

public:
	//������
	void Initialize(Character* chara, Character* enemy) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;

public:
	//�X�e�C�g��ύX
	void ChangeForwardState()   { m_search = static_cast<CharaState*>(m_forward.get());   }
	void ChangeBackwardState()  { m_search = static_cast<CharaState*>(m_backward.get());  }
	void ChangeLeftTurnState()  { m_search = static_cast<CharaState*>(m_leftTurn.get());  }
	void ChangeRightTurnState() { m_search = static_cast<CharaState*>(m_rightTurn.get()); }

private:
	//�X�e�C�g���삷��L�����N�^�[
	Character*                    m_chara;
	//�G�L�����N�^�[
	Character*                    m_enemy;
	//���݂̃X�e�[�g
	CharaState*				      m_search;
	//Forward���
	std::unique_ptr<Forward>      m_forward;
	//Backward���
	std::unique_ptr<Backward>     m_backward;	
	//LeftTurn���
	std::unique_ptr<LeftTurn>     m_leftTurn;
	//RightTurn���
	std::unique_ptr<RightTurn>    m_rightTurn;

};