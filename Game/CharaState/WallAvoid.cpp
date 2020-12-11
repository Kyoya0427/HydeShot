//======================================================
// File Name	: WallAvoid.cpp
// Summary		: 壁回避ステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

#include <Game/CharaState/CharaStateID.h>

#include <Game/GameObject/Character.h>
#include <Game/GameObject/WallApproachVelID.h>
#include <Game/GameObject/WallApproach.h>

#include <Game/UI/SelectStateUi.h>

/// <summary>
/// コンストラクタ
/// </summary>
WallAvoid::WallAvoid()
	: m_wallAvoid()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void WallAvoid::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);

	//ステイトを初期化
	m_forward   = std::make_unique<Forward>();
	m_backward  = std::make_unique<Backward>();
	m_leftward  = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_forward ->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_backward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_leftward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_rightward->Initialize(GetChara(), GetEnemy(), GetNeuralNetworkManager());

	//初期ステイト
	ChangeForwardState();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
	ChooseAction();
	//現在のステートの更新
	m_wallAvoid->Update(timer);
}

/// <summary>
/// 行動を選択
/// </summary>
void WallAvoid::ChooseAction()
{
	//相対座標
	float dis = DirectX::SimpleMath::Vector3::Distance(GetChara()->GetPosition(), GetEnemy()->GetPosition()) / 18.0f;
	//ステイト操作するキャラクターを原点とした絶対座標
	float x = GetChara()->GetPosition().x - GetEnemy()->GetPosition().x;

	//データから行動を選択
	if (GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::FORWARD || GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::BACKWARD)
	{
		if (x < 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"LEFTWARD");
			GetChara()->SetCharaState(CharaStateID::LEFTWARD);
			ChangeLeftwardState();
		}
		else if(x > 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"RIGHTWARD");
			GetChara()->SetCharaState(CharaStateID::RIGHTWARD);
			ChangeRightwardState();
		}
	}

	if (GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::LEFTWARD || GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::RIGHTWARD)
	{
		if (dis >= 0.45f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"FORWARD");
			GetChara()->SetCharaState(CharaStateID::FORWARD);
			ChangeForwardState();
		}
		else if (dis > 0.1f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"BACKWARD");
			GetChara()->SetCharaState(CharaStateID::BACKWARD);
			ChangeBackwardState();
		}
	}
}
