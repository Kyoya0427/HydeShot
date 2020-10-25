//======================================================
// File Name	: Rightward.cpp
// Summary		: 右移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Rightward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Rightward::Rightward()
	: m_chara()
	, m_enemy()
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
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Rightward::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Rightward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::RIGHT_ANGLE);
}