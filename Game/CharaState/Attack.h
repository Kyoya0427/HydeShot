//======================================================
// File Name	: Attack.h
// Summary		: �U���X�e�[�g
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
	//�f�X�g���N�^
	~Attack();

public:
	//������
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;

};