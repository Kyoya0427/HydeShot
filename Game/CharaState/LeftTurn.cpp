//======================================================
// File Name	: LeftTurn.cpp	
// Summary		: 左回転ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "LeftTurn.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// コンストラクタ
/// </summary>
LeftTurn::LeftTurn()
	: CharaState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
LeftTurn::~LeftTurn()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void LeftTurn::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void LeftTurn::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->LeftTurn(AIController::ROT_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}