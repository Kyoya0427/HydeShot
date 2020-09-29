//======================================================
// File Name	 : OptionList.cpp
// Summary		 : 選択肢リスト
// Author		 : Kyoya Sakamoto
//======================================================
#include "OptionList.h"

#include <Game/UI/Button.h>

/// <summary>
/// コンストラクタ
/// </summary>
OptionList::OptionList()
	: m_current(0)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
OptionList::~OptionList()
{
}

/// <summary>
/// 更新
/// </summary>
void OptionList::Update()
{

}

/// <summary>
/// 描画
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
/// 追加
/// </summary>
/// <param name="default">デフォルト画像</param>
/// <param name="select">選択中の画像</param>
/// <param name="pos">座標</param>
/// <param name="letter">表示文字</param>
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
/// 現在より一つ上に上げる
/// </summary>
void OptionList::CurrentUp()
{
	m_current = (m_current - 1 + m_button.size()) % m_button.size();
}

/// <summary>
/// 現在より一つ下に下げる
/// </summary>
void OptionList::CurrentDown()
{
	m_current = (m_current + 1 + m_button.size()) % m_button.size();
}

/// <summary>
/// テクスチャーを設定
/// </summary>
/// <param name="default">デフォルトテクスチャー</param>
/// <param name="select">セレクトテクスチャー</param>
void OptionList::SetTexture(ID3D11ShaderResourceView* default, ID3D11ShaderResourceView* select)
{
	m_defaultTexture = default;
	m_selectTexture = select;
}



