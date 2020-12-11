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
	: CharaState()
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
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Backward::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->Backward(AIController::MOVE_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::BACKWARD_ANGLE);
}