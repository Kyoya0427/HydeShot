//======================================================
// File Name	: GameStateManager.cpp
// Summary		: ゲームステイトマネジャー
//======================================================
#include "GameStateManager.h"

#include <cassert>

#include <Game/Common/Utilities.h>

#include <Game/GameState/IGameState.h>

/// <summary>
/// コンストラクタ
/// </summary>
GameStateManager::GameStateManager()
	:m_stateFactories()
	,m_states()
	,m_popCount(0)
	,m_nextStateName()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameStateManager::~GameStateManager()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void GameStateManager::Update(const DX::StepTimer& timer)
{
	if (m_popCount > 0)
	{
		for (int i = 0; i < m_popCount; i++)
		{
			m_states.back()->Finalize();
			m_states.pop_back();
		}
		m_popCount = 0;
	}

	if (m_nextStateName != GameState::NONE_STATE)
	{
		ChangeState();
	}

	assert(m_states.size() > 0 && "There is no active state.");
	m_states.back()->Update(timer);
}

/// <summary>
/// 描画
/// </summary>
void GameStateManager::Render()
{
	assert(m_states.size() > 0 && "There is no active state.");

	for (const IGameStatePtr& state : m_states)
	{
		state->Render();
	}
}

/// <summary>
/// 始めのステイトの初期設定
/// </summary>
/// <param name="id">ステイトID</param>
void GameStateManager::SetStartState(const GameState id)
{
	RequestState(id);
}

/// <summary>
/// 次のステイトの設定
/// </summary>
/// <param name="id">ステイトID</param>
void GameStateManager::RequestState(const GameState id)
{
	assert(m_stateFactories.count(id) != -1 && "A GameState with this name is not registered.");

	m_popCount = m_states.size();
	m_nextStateName = id;
}

/// <summary>
/// 既存ステイトにステイトを追加
/// </summary>
/// <param name="id">ステイトID</param>
void GameStateManager::PushState(const GameState id)
{
	m_nextStateName = id;
}

/// <summary>
/// 追加ステイトを消去
/// </summary>
/// <param name="count">カウント</param>
void GameStateManager::PopState(int count)
{
	assert(count > 0 && "Count is invalid.");
	if (m_nextStateName != GameState::NONE_STATE)
	{
		m_nextStateName = GameState::NONE_STATE;
	}
	m_popCount = Clamp<int>(m_popCount + count, 0, m_states.size() - 1);

}

/// <summary>
/// ステイトを変更
/// </summary>
void GameStateManager::ChangeState()
{
	m_states.push_back(m_stateFactories[m_nextStateName]());
	m_states.back()->Initialize();

	m_nextStateName = GameState::NONE_STATE;
}