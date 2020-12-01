//======================================================
// File Name	: Search.h
// Summary		: �T�[�`�̃X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "Search.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Search::Search()
	: m_search()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Search::~Search()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="enemy">�G�L�����N�^�[</param>
void Search::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;

	//�X�e�C�g��������
	m_forward    = std::make_unique<Forward>();
	m_backward   = std::make_unique<Backward>();
	m_leftTurn   = std::make_unique<LeftTurn>();
	m_rightTurn  = std::make_unique<RightTurn>();

	m_forward->Initialize  (m_chara, m_enemy, m_neuralNetwork);
	m_backward->Initialize (m_chara, m_enemy, m_neuralNetwork);
	m_leftTurn->Initialize (m_chara, m_enemy, m_neuralNetwork);
	m_rightTurn->Initialize(m_chara, m_enemy, m_neuralNetwork);

	//�����X�e�C�g
	ChangeForwardState();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Search::Update(const DX::StepTimer& timer)
{
	ChooseAction();
	//���݂̃X�e�[�g�̍X�V
	m_search->Update(timer);
}

/// <summary>
/// �s����I��
/// </summary>
void Search::ChooseAction()
{
	NeuralNetworkManager::OutputData data = m_neuralNetwork->GetOutputData();

	float dis = data.outputDis;
	float left = data.outputLeft;
	float right = data.outputRight;

	//�o�̓f�[�^����s����I��
	if (left >= 0.5f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"LEFT_TURN");
		ChangeLeftTurnState();
		m_chara->SetCharaState(CharaStateID::LEFT_TURN);
	}
	else if (right >= 0.5f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"RIGHT_TURN");
		ChangeRightTurnState();
		m_chara->SetCharaState(CharaStateID::RIGHT_TURN);
	}
	else if (dis >= 0.45f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"FORWARD");
		ChangeForwardState();
		m_chara->SetCharaState(CharaStateID::FORWARD);
	}
	else if (dis >= 0.0f)
	{
		GameContext::Get<SelectStateUi>()->SetSelectState(L"BACKWARD");
		ChangeBackwardState();
		m_chara->SetCharaState(CharaStateID::BACKWARD);
	}
}