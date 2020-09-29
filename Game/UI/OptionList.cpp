//======================================================
// File Name	 : OptionList.cpp
// Summary		 : �I�������X�g
// Author		 : Kyoya Sakamoto
//======================================================
#include "OptionList.h"

#include <Game/UI/Button.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
OptionList::OptionList()
	: m_current(0)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OptionList::~OptionList()
{
}

/// <summary>
/// �X�V
/// </summary>
void OptionList::Update()
{

}

/// <summary>
/// �`��
/// </summary>
void OptionList::Render()
{
	for (const auto& button : m_button)
	{
		button->SetSelect(false);
	}
	m_button[m_current]->SetSelect(true);
	for (const auto& button : m_button)
	{
		button->Render();
	}
}

/// <summary>
/// �ǉ�
/// </summary>
/// <param name="default">�f�t�H���g�摜</param>
/// <param name="select">�I�𒆂̉摜</param>
/// <param name="pos">���W</param>
/// <param name="letter">�\������</param>
void OptionList::Add(DirectX::SimpleMath::Vector2 pos, wchar_t* letter)
{
	std::unique_ptr<Button> button = std::make_unique<Button>();
	button->Initialize(pos, letter);
	button->SetDefaultTexture(m_defaultTexture);
	button->SetSelectTexture(m_selectTexture);
	button->SetSelect(false);

	m_button.push_back(std::move(button));

}

/// <summary>
/// ���݂����ɏグ��
/// </summary>
void OptionList::CurrentUp()
{
	m_current = (m_current - 1 + m_button.size()) % m_button.size();
}

/// <summary>
/// ���݂�����ɉ�����
/// </summary>
void OptionList::CurrentDown()
{
	m_current = (m_current + 1 + m_button.size()) % m_button.size();
}

/// <summary>
/// �e�N�X�`���[��ݒ�
/// </summary>
/// <param name="default">�f�t�H���g�e�N�X�`���[</param>
/// <param name="select">�Z���N�g�e�N�X�`���[</param>
void OptionList::SetTexture(ID3D11ShaderResourceView* default, ID3D11ShaderResourceView* select)
{
	m_defaultTexture = default;
	m_selectTexture = select;
}



