//======================================================
// File Name	: Attack.cpp
// Summary		: 攻撃ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/UI/SelectStateUi.h>

/// <summary>
/// コンストラクタ
/// </summary>
Attack::Attack()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Attack::~Attack()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="enemy">敵キャラクター</param>
void Attack::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Attack::Update(const DX::StepTimer& timer)
{
	timer;
	GameContext::Get<SelectStateUi>()->SetSelectState(L"SHOOT");
	m_chara->Shoot();
}