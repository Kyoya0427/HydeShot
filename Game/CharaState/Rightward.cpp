//======================================================
// File Name	: Rightward.cpp
// Summary		: �E�ړ��X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "Rightward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Rightward::Rightward()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Rightward::~Rightward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�R���g���[���[</param>
void Rightward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Rightward::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Rightward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::RIGHT_ANGLE);
}