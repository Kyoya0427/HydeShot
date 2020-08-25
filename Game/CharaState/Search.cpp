//======================================================
// File Name	: Search.h
// Summary		: �T�[�`�̃X�e�[�g
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
/// �R���X�g���N�^
/// </summary>
Search::Search()
	: m_chara()
	, m_enemy()
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
void Search::Initialize(Character* chara, Character* enemy)
{
	m_chara      = chara;
	m_enemy      = enemy;

	//�X�e�C�g��������
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

	//�����X�e�C�g
	ChangeStandingState();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Search::Update(const DX::StepTimer& timer)
{
	NeuralNetwork* data = GameContext::Get<NeuralNetworkManager>()->m_neuralNetwork.get();

	float dis   = data->GetOutput(0);
	float left  = data->GetOutput(1);
	float right = data->GetOutput(2);

	//�o�̓f�[�^����s����I��
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

	//���݂̃X�e�[�g�̍X�V
	m_search->Update(timer);
}

/// <summary>
/// �`��
/// </summary>
void Search::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, static_cast<Color>(Colors::White), 1.0f, L"Search");
	debugFont->draw();
	//���݂̃X�e�[�g�̕`��
	m_search->Render();
}

