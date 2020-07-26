//======================================================
// File Name	: WallAvoid.h
// Summary		: �ǉ���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
WallAvoid::WallAvoid()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara"></param>
void WallAvoid::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	
	m_leftward = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_leftward->Initialize(m_chara, m_controller);
	m_rightward->Initialize(m_chara, m_controller);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
	float direction = m_chara->GetRadiansY();

	if (direction >= DirectX::XM_PI)
		ChangeLeftwardState();
	else 
		ChangeRightwardState();


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
	m_wallAvoid->Render();
}

/// <summary>
/// Leftward�ɕύX
/// </summary>
void WallAvoid::ChangeLeftwardState()
{
	m_wallAvoid = static_cast<CharaState*>(m_leftward.get());
}

/// <summary>
/// Rightward�ɕύX
/// </summary>
void WallAvoid::ChangeRightwardState()
{
	m_wallAvoid = static_cast<CharaState*>(m_rightward.get());
}
