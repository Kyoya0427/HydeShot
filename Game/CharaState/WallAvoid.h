//======================================================
// File Name	: WallAvoid.h
// Summary		: �ǉ���X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/CharaState/Forward.h>
#include <Game/CharaState/Backward.h>
#include <Game/CharaState/Leftward.h>
#include <Game/CharaState/Rightward.h>

#include <Game/Controller/CharacterController.h>

class WallAvoid : public CharaState
{
public:
	//�R���X�g���N�^
	WallAvoid();

public:
	//������
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�s����I��
	void ChooseAction();

public:
	//�X�e�C�g��ύX
	void ChangeForwardState()   { m_wallAvoid = m_forward.get();   }
	void ChangeBackwardState()  { m_wallAvoid = m_backward.get();  }
	void ChangeLeftwardState()  { m_wallAvoid = m_leftward.get();  }
	void ChangeRightwardState() { m_wallAvoid = m_rightward.get(); }

private:
	//�X�e�C�g���삷��L�����N�^�[
	Character*                      m_chara;
	//�G�L�����N�^�[
	Character*                      m_enemy;
	//���݂̃X�e�[�g
	CharaState*                     m_wallAvoid;

	//Forward���
	std::unique_ptr<Forward>		m_forward;
	//Backward���
	std::unique_ptr<Backward>		m_backward;
	//Leftward���
	std::unique_ptr<Leftward>		m_leftward;
	//Rightward���
	std::unique_ptr<Rightward>      m_rightward;

};