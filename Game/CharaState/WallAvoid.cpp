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

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
WallAvoid::WallAvoid()
	: m_chara()
	, m_enemy()
	, m_wallAvoid()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void WallAvoid::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;

	//ステイトを初期化
	m_forward   = std::make_unique<Forward>();
	m_backward  = std::make_unique<Backward>();
	m_leftward  = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_forward ->Initialize (m_chara, m_enemy, m_neuralNetwork);
	m_backward->Initialize (m_chara, m_enemy, m_neuralNetwork);
	m_leftward->Initialize (m_chara, m_enemy, m_neuralNetwork);
	m_rightward->Initialize(m_chara, m_enemy, m_neuralNetwork);

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
	float dis = Vector3::Distance(m_chara->GetPosition(), m_enemy->GetPosition()) / 18.0f;
	//ステイト操作するキャラクターを原点とした絶対座標
	float x = m_chara->GetPosition().x - m_enemy->GetPosition().x;

	//データから行動を選択
	if (m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::FORWARD || m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::BACKWARD)
	{
		if (x < 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"LEFTWARD");
			m_chara->SetCharaState(CharaStateID::LEFTWARD);
			ChangeLeftwardState();
		}
		else if(x > 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"RIGHTWARD");
			m_chara->SetCharaState(CharaStateID::RIGHTWARD);
			ChangeRightwardState();
		}
	}

	if (m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::LEFTWARD || m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::RIGHTWARD)
	{
		if (dis >= 0.45f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"FORWARD");
			m_chara->SetCharaState(CharaStateID::FORWARD);
			ChangeForwardState();
		}
		else if (dis > 0.1f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"BACKWARD");
			m_chara->SetCharaState(CharaStateID::BACKWARD);
			ChangeBackwardState();
		}
	}
}
