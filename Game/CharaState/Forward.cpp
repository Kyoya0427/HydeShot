//======================================================
// File Name	: Forward.cpp
// Summary		: �O�ړ��X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "Forward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
Forward::Forward()
	: CharaState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Forward::~Forward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void Forward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Forward::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->Forward(AIController::MOVE_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}