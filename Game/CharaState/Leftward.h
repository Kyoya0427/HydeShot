//======================================================
// File Name	: Leftward.h
// Summary		: ���ړ��X�e�[�g
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
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;

};