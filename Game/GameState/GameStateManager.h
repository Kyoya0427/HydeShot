//======================================================
// File Name	: GameStateManager.h
// Summary		: ゲームステイトマネジャー
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
		SELECT_STATE,
		PLAY_STATE,
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
	//始めのステイトの初期設定
	void SetStartState(const GameState id);
	//ステイトを登録
	template<typename State>
	void RegisterState(const GameState id);
	//次のステイトの設定
	void RequestState(const GameState id);
	//既存ステイトにステイトを追加
	void PushState(const GameState id);
	//追加ステイトを消去
	void PopState(int count = 1);

private:
	//ステイトを変更
	void ChangeState();

private:
	//使用するステートのリスト
	IGameStateFactoryList m_stateFactories;
	//現在のステート
	IGameStateStack       m_states;
	//ステートの数
	int                   m_popCount;
	//次のステート登録
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
/// <param name="id">ステイトID</param>
 void GameStateManager::RegisterState(const GameState id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}