//======================================================
// File Name	: Backward.h
// Summary		: ���ړ��X�e�[�g
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

};