//======================================================
// File Name	: CharaState.h
// Summary		: �L�����̃X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/Character.h>

#include <Game/Common/StepTimer.h>

class Character;
class CharacterController;
class NeuralNetworkManager;

class CharaState
{
public:
	//�f�X�g���N�^
	virtual ~CharaState() = default;

public:
	//������
	virtual void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) = 0;
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;

protected:

	NeuralNetworkManager*		m_neuralNetwork;
};