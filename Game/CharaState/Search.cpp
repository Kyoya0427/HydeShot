//======================================================
// File Name	: Search.h
// Summary		: �T�[�`�̃X�e�[�g
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Search.h"

#include <Game/Common/DebugFont.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Search::Search()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="chara"></param>
void Search::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void Search::Update(const DX::StepTimer& timer)
{
	timer;

}

/// <summary>
/// �`��
/// </summary>
void Search::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"Search");
	debugFont->draw();
}
