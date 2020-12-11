//======================================================
// File Name	: RightTurn.cpp
// Summary		: 右回転ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "RightTurn.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// コンストラクタ
/// </summary>
RightTurn::RightTurn()
	: CharaState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RightTurn::~RightTurn()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void RightTurn::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void RightTurn::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->RightTurn(AIController::ROT_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}