//======================================================
// File Name	: GameStateManager.h
// Summary	: ゲームステイトマネジャー
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <functional>
#include <memory>
#include <deque>
#include <unordered_map>
#include <Framework\StepTimer.h>

class IGameState;

class GameStateManager
{
public:
	//ステイトID
	enum GameStateID
	{
		NONE_STATE = -1,
		TITLE_STATE,
		PLAY_STATE,
		PAUSE_STATE,
		RESULT_STATE,
	};

private:
	//名前変更
	using IGameStatePtr         = std::unique_ptr<IGameState>;
	using IGameStateStack       = std::deque<IGameStatePtr>;
	using IGameStateFactory     = std::function<IGameStatePtr()>;
	using IGameStateFactoryList = std::unordered_map<GameStateID, IGameStateFactory>;


public:
	GameStateManager();
	~GameStateManager();

private:
	template<typename State>
	static IGameStatePtr CrateState();

public:
	
	void Update(const DX::StepTimer& timer);
	void Render(const DX::StepTimer& timer);

public:
	template<typename State>
	void RegisterState(const GameStateID id);
	
	void SetStartState(const GameStateID id);

	void RequestState(const GameStateID id);
	void PushState(const GameStateID id);
	void PopState(int count = 1);

	

private:
	void ChangeState();

private:
	IGameStateFactoryList m_stateFactories;
	IGameStateStack       m_states;
	int                   m_popCount;
	GameStateID           m_nextStateName;
};


template<typename State>
/// <summary>
/// ステイト作成
/// </summary>
/// <returns></returns>
 GameStateManager::IGameStatePtr GameStateManager::CrateState()
{
	return std::make_unique<State>();
}



template<typename State>
/// <summary>
///  ステイトを登録
/// </summary>
/// <param name="id"></param>
 void GameStateManager::RegisterState(const GameStateID id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}
