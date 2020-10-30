//======================================================
// File Name	: RightTurn.cpp
// Summary		: �E��]�X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "RightTurn.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
RightTurn::RightTurn()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RightTurn::~RightTurn()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void RightTurn::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void RightTurn::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->RightTurn(AIController::ROT_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}