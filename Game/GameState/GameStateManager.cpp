//======================================================
// File Name	: GameStateManager.cpp
// Summary		: �Q�[���X�e�C�g�}�l�W���[
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "GameStateManager.h"

#include <cassert>

#include <Game\Common\Utilities.h>

#include <Game/GameState/IGameState.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameStateManager::GameStateManager()
	:m_stateFactories()
	,m_states()
	,m_popCount(0)
	,m_nextStateName()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameStateManager::~GameStateManager()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
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
/// �`��
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
/// �n�߂̃X�e�C�g�̏����ݒ�
/// </summary>
/// <param name="id">�X�e�C�gID</param>
void GameStateManager::SetStartState(const GameState id)
{
	RequestState(id);
}

/// <summary>
/// ���̃X�e�C�g�̐ݒ�
/// </summary>
/// <param name="id">�X�e�C�gID</param>
void GameStateManager::RequestState(const GameState id)
{
	assert(m_stateFactories.count(id) != -1 && "A GameState with this name is not registered.");

	m_popCount = m_states.size();
	m_nextStateName = id;
}

/// <summary>
/// �����X�e�C�g�ɃX�e�C�g��ǉ�
/// </summary>
/// <param name="id">�X�e�C�gID</param>
void GameStateManager::PushState(const GameState id)
{
	m_nextStateName = id;
}

/// <summary>
/// �ǉ��X�e�C�g������
/// </summary>
/// <param name="count"></param>
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
/// �X�e�C�g��ύX
/// </summary>
void GameStateManager::ChangeState()
{
	m_states.push_back(m_stateFactories[m_nextStateName]());
	m_states.back()->Initialize();

	m_nextStateName = GameState::NONE_STATE;
}

