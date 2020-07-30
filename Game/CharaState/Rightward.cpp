//======================================================
// File Name	: Rightward.h
// Summary		: �E�ړ��X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Rightward.h"


#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Rightward::Rightward()
	: m_chara()
	, m_enemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Rightward::~Rightward()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara">�X�e�C�g���삷��L�����N�^�[</param>
/// <param name="controller">�R���g���[���[</param>
void Rightward::Initialize(Character* chara, Character* enemy)
{
	m_chara      = chara;
	m_enemy      = enemy;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Rightward::Update(const DX::StepTimer& timer)
{
	timer;
	float direction = m_chara->GetRadiansY();

	if (direction > DirectX::XM_PI)
		GameContext::Get<WallAvoid>()->ChangeLeftwardState();

	m_chara->Rightward(AIController::MOVE_SPEED);
}

/// <summary>
/// �`��
/// </summary>
void Rightward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Rightward");
	debugFont->draw();
}
