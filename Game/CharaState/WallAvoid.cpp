//======================================================
// File Name	: WallAvoid.cpp
// Summary		: �ǉ���X�e�[�g
// Date			: 2020/7/23
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


using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
WallAvoid::WallAvoid()
	: m_chara()
	, m_enemy()
	, m_wallAvoid()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara"></param>
void WallAvoid::Initialize(Character* chara, Character* enemy)
{
	m_chara = chara;
	m_enemy = enemy;

	//�X�e�C�g��������
	m_forward   = std::make_unique<Forward>();
	m_backward  = std::make_unique<Backward>();
	m_leftward  = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_forward ->Initialize (m_chara, m_enemy);
	m_backward->Initialize (m_chara, m_enemy);
	m_leftward->Initialize (m_chara, m_enemy);
	m_rightward->Initialize(m_chara, m_enemy);

	//�����X�e�C�g
	ChangeForwardState();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{

	float dis = Vector3::Distance(m_chara->GetPosition(), m_enemy->GetPosition()) / 18.0f;
	
	float z = m_chara->GetPosition().x - m_enemy->GetPosition().x;

	//�f�[�^����s����I��

	if (m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::FORWARD || m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::BACKWARD)
	{
		if (z < 0.0f)
		{
			m_chara->SetCharaState(CharaStateID::LEFTWARD);
			ChangeLeftwardState();
		}
		else
		{
			m_chara->SetCharaState(CharaStateID::RIGHTWARD);	
			ChangeRightwardState();
		}
	}

	if (m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::LEFTWARD || m_chara->GetWallApproachVel()->GetWallApproach() == WallApproachVelID::RIGHTWARD)
	{
		if (dis >= 0.45f)
		{
			m_chara->SetCharaState(CharaStateID::FORWARD);		
			ChangeForwardState();
		}
		else if (dis > 0.1f)
		{
			m_chara->SetCharaState(CharaStateID::BACKWARD);
			ChangeBackwardState();
		}
	}

	//���݂̃X�e�[�g�̍X�V
	m_wallAvoid->Update(timer);
}


/// <summary>
/// �`��
/// </summary>
void WallAvoid::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"WallAvoid");
	debugFont->draw();

	//���݂̃X�e�[�g�̕`��
	m_wallAvoid->Render();
}

