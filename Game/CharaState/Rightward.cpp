//======================================================
// File Name	: Rightward.cpp
// Summary		: 右移動ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "Rightward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

/// <summary>
/// コンストラクタ
/// </summary>
Rightward::Rightward()
	: CharaState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Rightward::~Rightward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void Rightward::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Rightward::Update(const DX::StepTimer& timer)
{
	timer;
	GetChara()->Rightward(AIController::MOVE_SPEED);
	GetChara()->GetWallApproachVel()->SetOffsetAngle(WallApproach::RIGHT_ANGLE);
}