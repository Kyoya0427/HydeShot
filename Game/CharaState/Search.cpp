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

/// <summary>
/// コンストラクタ
/// </summary>
Search::Search()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void Search::Initialize(Character* chara, CharacterController* controller)
{
	m_chara      = chara;
	m_controller = controller;

	m_standing   = std::make_unique<Standing>();
	m_forward    = std::make_unique<Forward>();
	m_backward   = std::make_unique<Backward>();
	m_leftTurn   = std::make_unique<LeftTurn>();
	m_rightTurn  = std::make_unique<RightTurn>();

	m_standing->Initialize(m_chara, m_controller);
	m_forward->Initialize(m_chara, m_controller);
	m_backward->Initialize(m_chara, m_controller);
	m_leftTurn->Initialize(m_chara, m_controller);
	m_rightTurn->Initialize(m_chara, m_controller);

	ChangeStandingState();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void Search::Update(const DX::StepTimer& timer)
{
	NeuralNetworkManager::OutputData data = GameContext::Get<NeuralNetworkManager>()->m_data;

	float dis   = data.outputDis;
	float left  = data.outputLeft;
	float right = data.outputRight;


	if (left >= 0.8f)
		ChangeLeftTurnState();
	else if (right >= 0.8f)
		ChangeRightTurnState();
	else if (dis >= 0.4f)
		ChangeForwardState();
	else if (dis >= 0.1f)
		ChangeBackwardState();


	m_search->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
void Search::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"Search");
	debugFont->draw();
	m_search->Render();
}

/// <summary>
/// Standingに変更
/// </summary>
void Search::ChangeStandingState()
{
	m_search = static_cast<CharaState*>(m_standing.get());
}

/// <summary>
/// Forwardに変更
/// </summary>
void Search::ChangeForwardState()
{
	m_search = static_cast<CharaState*>(m_forward.get());
}

/// <summary>
/// Backwardに変更
/// </summary>
void Search::ChangeBackwardState()
{
	m_search = static_cast<CharaState*>(m_backward.get());
}

/// <summary>
/// LeftTurnに変更
/// </summary>
void Search::ChangeLeftTurnState()
{
	m_search = static_cast<CharaState*>(m_leftTurn.get());
}

/// <summary>
/// RightTurn変更
/// </summary>
void Search::ChangeRightTurnState()
{
	m_search = static_cast<CharaState*>(m_rightTurn.get());
}
