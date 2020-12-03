//======================================================
// File Name	: Backward.cpp
// Summary		: 後ろ移動ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "Backward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// コンストラクタ
/// </summary>
Backward::Backward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Backward::~Backward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void Backward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Backward::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Backward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::BACKWARD_ANGLE);
}