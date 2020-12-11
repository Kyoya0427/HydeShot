//======================================================
// File Name	: WallAvoid.cpp
// Summary		: �ǉ���X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

#include <Game/CharaState/CharaStateID.h>

#include <Game/GameObject/Character.h>
#include <Game/GameObject/WallApproachVelID.h>
#include <Game/GameObject/WallApproach.h>

#include <Game/UI/SelectStateUi.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
WallAvoid::WallAvoid()
	: m_wallAvoid()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�G�L�����N�^�[</param>
void WallAvoid::Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork)
{
	SetChara(chara);
	SetEnemy(enemy);
	SetNeuralNetworkManager(neuralNetwork);

	//�X�e�C�g��������
	m_forward   = std::make_unique<Forward>();
	m_backward  = std::make_unique<Backward>();
	m_leftward  = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_forward ->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_backward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_leftward->Initialize (GetChara(), GetEnemy(), GetNeuralNetworkManager());
	m_rightward->Initialize(GetChara(), GetEnemy(), GetNeuralNetworkManager());

	//�����X�e�C�g
	ChangeForwardState();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
	ChooseAction();
	//���݂̃X�e�[�g�̍X�V
	m_wallAvoid->Update(timer);
}

/// <summary>
/// �s����I��
/// </summary>
void WallAvoid::ChooseAction()
{
	//���΍��W
	float dis = DirectX::SimpleMath::Vector3::Distance(GetChara()->GetPosition(), GetEnemy()->GetPosition()) / 18.0f;
	//�X�e�C�g���삷��L�����N�^�[�����_�Ƃ�����΍��W
	float x = GetChara()->GetPosition().x - GetEnemy()->GetPosition().x;

	//�f�[�^����s����I��
	if (GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::FORWARD || GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::BACKWARD)
	{
		if (x < 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"LEFTWARD");
			GetChara()->SetCharaState(CharaStateID::LEFTWARD);
			ChangeLeftwardState();
		}
		else if(x > 0.0f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"RIGHTWARD");
			GetChara()->SetCharaState(CharaStateID::RIGHTWARD);
			ChangeRightwardState();
		}
	}

	if (GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::LEFTWARD || GetChara()->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::RIGHTWARD)
	{
		if (dis >= 0.45f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"FORWARD");
			GetChara()->SetCharaState(CharaStateID::FORWARD);
			ChangeForwardState();
		}
		else if (dis > 0.1f)
		{
			GameContext::Get<SelectStateUi>()->SetSelectState(L"BACKWARD");
			GetChara()->SetCharaState(CharaStateID::BACKWARD);
			ChangeBackwardState();
		}
	}
}
