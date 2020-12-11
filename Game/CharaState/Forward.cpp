//======================================================
// File Name	: Forward.cpp
// Summary		: 前移動ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "Forward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>


/// <summary>
/// コンストラクタ
/// </summary>
Forward::Forward()
	: CharaState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Forward::~Forward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void Forward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Forward::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->Forward(AIController::MOVE_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}