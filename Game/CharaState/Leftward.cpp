//======================================================
// File Name	: Leftward.cpp
// Summary		: ���ړ��X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "Leftward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Leftward::Leftward()
	: CharaState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Leftward::~Leftward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void Leftward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Leftward::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->Leftward(AIController::MOVE_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::LEFT_ANGLE);
}