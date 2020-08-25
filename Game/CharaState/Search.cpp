//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Search.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Search::Search()
	: m_chara()
	, m_enemy()
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
void Search::Initialize(Character* chara, Character* enemy)
{
	m_chara      = chara;
	m_enemy      = enemy;

	//ステイトを初期化
	m_standing   = std::make_unique<Standing>();
	m_forward    = std::make_unique<Forward>();
	m_backward   = std::make_unique<Backward>();
	m_leftTurn   = std::make_unique<LeftTurn>();
	m_rightTurn  = std::make_unique<RightTurn>();

	m_standing->Initialize (m_chara, m_enemy);
	m_forward->Initialize  (m_chara, m_enemy);
	m_backward->Initialize (m_chara, m_enemy);
	m_leftTurn->Initialize (m_chara, m_enemy);
	m_rightTurn->Initialize(m_chara, m_enemy);

	//初期ステイト
	ChangeStandingState();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Search::Update(const DX::StepTimer& timer)
{
	NeuralNetwork* data = GameContext::Get<NeuralNetworkManager>()->m_neuralNetwork.get();

	float dis   = data->GetOutput(0);
	float left  = data->GetOutput(1);
	float right = data->GetOutput(2);

	//出力データから行動を選択
	if (left >= 0.5f)
	{
		ChangeLeftTurnState();
		m_chara->SetCharaState(CharaStateID::LEFT_TURN);
	}
	else if (right >= 0.5f)
	{
		ChangeRightTurnState();
		m_chara->SetCharaState(CharaStateID::RIGHT_TURN);
	}
	else if (dis >= 0.45f)
	{
		ChangeForwardState();
		m_chara->SetCharaState(CharaStateID::FORWARD);
	}
	else if (dis >= 0.0f)
	{
		ChangeBackwardState();
		m_chara->SetCharaState(CharaStateID::BACKWARD);
	}

	//現在のステートの更新
	m_search->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
void Search::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, static_cast<Color>(Colors::White), 1.0f, L"Search");
	debugFont->draw();
	//現在のステートの描画
	m_search->Render();
}

