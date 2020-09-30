//======================================================
// File Name	: Backward.h
// Summary		: ���ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Backward : public CharaState
{
public:
	//�R���X�g���N�^
	Backward();
	//�f�X�g���N�^
	~Backward();

public:
	//������
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;

private:
	//�X�e�C�g���삷��L�����N�^�[
	Character*		m_chara;
	//�G�L�����N�^�[
	Character*		m_enemy;

};