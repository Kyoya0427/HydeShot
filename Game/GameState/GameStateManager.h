//======================================================
// File Name	: GameStateManager.h
// Summary		: �Q�[���X�e�C�g�}�l�W���[
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
	//�X�e�C�gID
	enum class GameState
	{
		NONE_STATE = -1,
		TITLE_STATE,
		SELECT_STATE,
		PLAY_STATE,
		RESULT_STATE,
	};

private:
	//���O�ύX
	using IGameStatePtr         = std::unique_ptr<IGameState>;
	using IGameStateStack       = std::deque<IGameStatePtr>;
	using IGameStateFactory     = std::function<IGameStatePtr()>;
	using IGameStateFactoryList = std::unordered_map<GameState, IGameStateFactory>;

public:
	//�R���X�g���N�^
	GameStateManager();
	//�f�X�g���N�^
	~GameStateManager();

private:
	//�X�e�C�g���쐬
	template<typename State>
	static IGameStatePtr CrateState();

public:
	//�X�V
	void Update(const DX::StepTimer& timer);
	//�`��
	void Render();

public:
	//�n�߂̃X�e�C�g�̏����ݒ�
	void SetStartState(const GameState id);
	//�X�e�C�g��o�^
	template<typename State>
	void RegisterState(const GameState id);
	//���̃X�e�C�g�̐ݒ�
	void RequestState(const GameState id);
	//�����X�e�C�g�ɃX�e�C�g��ǉ�
	void PushState(const GameState id);
	//�ǉ��X�e�C�g������
	void PopState(int count = 1);

private:
	//�X�e�C�g��ύX
	void ChangeState();

private:
	//�g�p����X�e�[�g�̃��X�g
	IGameStateFactoryList m_stateFactories;
	//���݂̃X�e�[�g
	IGameStateStack       m_states;
	//�X�e�[�g�̐�
	int                   m_popCount;
	//���̃X�e�[�g�o�^
	GameState             m_nextStateName;

};

template<typename State>
/// <summary>
/// �X�e�C�g�쐬
/// </summary>
/// <returns></returns>
 GameStateManager::IGameStatePtr GameStateManager::CrateState()
{
	return std::make_unique<State>();
}

template<typename State>
/// <summary>
///  �X�e�C�g��o�^
/// </summary>
/// <param name="id">�X�e�C�gID</param>
 void GameStateManager::RegisterState(const GameState id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}