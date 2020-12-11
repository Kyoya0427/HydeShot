//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Author		: Kyoya  Sakamoto
//======================================================
#include "Search.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

#include <Game/UI/SelectStateUi.h>

/// <summary>
/// コンストラクタ
/// </summary>
Search::Search()
	: CharaState()
	, m_search()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Search::~Search()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="enemy">敵キャラクター</param>
void Search::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);

	//ステイトを初期化
	m_forward    = std::make_unique<Forward>();
	m_backward   = std::make_unique<Backward>();
	m_leftTurn   = std::make_unique<LeftTurn>();
	m_rightTurn  = std::make_unique<RightTurn>();

	m_forward->Initialize  (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_backward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_leftTurn->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_rightTurn->Initialize(GetChara(), GetEnemy(), GetNeuralNetworkManager());

	//初期ステイト
	ChangeForwardState();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Search::Update(const DX::StepTimer& timer)
{
	ChooseAction();
	//現在のステートの更新
	m_search->Update(timer);
}

/// <summary>
/// 行動を選択
/// </summary>
void Search::ChooseAction()
{
	NeuralNetworkManager::OutputData data = GetNeuralNetworkManager()->GetOutputData();

	float dis = data.outputDis;
	float left = data.outputLeft;
	float right = data.outputRight;

	//出力データから行動を選択
	if (left >= 0.5f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"LEFT_TURN");
		ChangeLeftTurnState();
		GetChara()->SetCharaState(CharaStateID::LEFT_TURN);
	}
	else if (right >= 0.5f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"RIGHT_TURN");
		ChangeRightTurnState();
		GetChara()->SetCharaState(CharaStateID::RIGHT_TURN);
	}
	else if (dis >= 0.45f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"FORWARD");
		ChangeForwardState();
		GetChara()->SetCharaState(CharaStateID::FORWARD);
	}
	else if (dis >= 0.0f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"BACKWARD");
		ChangeBackwardState();
		GetChara()->SetCharaState(CharaStateID::BACKWARD);
	}
}