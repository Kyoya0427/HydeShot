//======================================================
// File Name	: WallAvoid.h
// Summary		: �ǉ���X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>

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
void WallAvoid::Initialize(Character* chara)
{
	m_chara = chara;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// �`��
/// </summary>
void WallAvoid::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"WallAvoid");
	debugFont->draw();
}
