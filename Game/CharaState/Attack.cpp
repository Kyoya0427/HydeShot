//======================================================
// File Name	: Attack.cpp
// Summary		: �U���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Attack::Attack()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Attack::~Attack()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="enemy">�G�L�����N�^�[</param>
void Attack::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	m_chara         = chara;
	m_enemy         = enemy;
	m_neuralNetwork = neuralNetwork;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Attack::Update(const DX::StepTimer& timer)
{
	timer;
	GameContext::Get<SelectStateUi>()->SetSelectState(L"SHOOT");
	m_chara->Shoot();
}