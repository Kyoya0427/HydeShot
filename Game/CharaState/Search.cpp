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

/// <summary>
/// �R���X�g���N�^
/// </summary>
Search::Search()
	: CharaState()
	, m_search()
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
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);

	//�X�e�C�g��������
	m_forward    = std::make_unique<Forward>();
	m_backward   = std::make_unique<Backward>();
	m_leftTurn   = std::make_unique<LeftTurn>();
	m_rightTurn  = std::make_unique<RightTurn>();

	m_forward->Initialize  (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_backward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_leftTurn->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_rightTurn->Initialize(GetChara(), GetEnemy(), GetNeuralNetworkManager());

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
	NeuralNetworkManager::OutputData data = GetNeuralNetworkManager()->GetOutputData();

	float dis = data.outputDis;
	float left = data.outputLeft;
	float right = data.outputRight;

	//�o�̓f�[�^����s����I��
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