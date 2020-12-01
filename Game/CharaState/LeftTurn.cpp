//======================================================
// File Name	: LeftTurn.cpp	
// Summary		: ����]�X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "LeftTurn.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
LeftTurn::LeftTurn()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LeftTurn::~LeftTurn()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void LeftTurn::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void LeftTurn::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->LeftTurn(AIController::ROT_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}