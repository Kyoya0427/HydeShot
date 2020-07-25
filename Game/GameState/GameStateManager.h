//======================================================
// File Name	: GameStateManager.h
// Summary		: ゲームステイトマネジャー
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <functional>
#include <memory>
#include <deque>
#include <unordered_map>

#include <Game/Common/StepTimer.h>

class IGameState;

class GameStateManager
{
public:
	//ステイトID
	enum class GameState
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
	using IGameStateFactoryList = std::unordered_map<GameState, IGameStateFactory>;

public:
	//コンストラクタ
	GameStateManager();
	//デストラクタ
	~GameStateManager();

private:
	//ステイトを作成
	template<typename State>
	static IGameStatePtr CrateState();

public:
	//更新
	void Update(const DX::StepTimer& timer);
	//描画
	void Render();

public:

	template<typename State>
	void RegisterState(const GameState id);
	void SetStartState(const GameState id);
	void RequestState(const GameState id);
	void PushState(const GameState id);
	void PopState(int count = 1);

private:
	void ChangeState();

private:
	IGameStateFactoryList m_stateFactories;
	IGameStateStack       m_states;
	int                   m_popCount;
	GameState             m_nextStateName;

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
 void GameStateManager::RegisterState(const GameState id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}
