//======================================================
// File Name	: Button.cpp
// Summary		: UIボタン
// Author		: Kyoya Sakamoto
//======================================================
#include "Button.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// コンストラクタ
/// </summary>
Button::Button()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Button::~Button()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">座標</param>
/// <param name="letter">表示文字</param>
void Button::Initialize(const DirectX::SimpleMath::Vector2& pos, wchar_t* letter)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());

	m_position = pos;
	m_letter   = letter;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Button::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void Button::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, GameContext::Get<DirectX::CommonStates>()->NonPremultiplied());
	if (m_isSelect)
		m_spriteBatch->Draw(m_selectTexture.Get(), m_position);
	else
		m_spriteBatch->Draw(m_defaultTexture.Get(), m_position);
	m_spriteBatch->End();

	debugFont->print(m_position.x + 40.0f, m_position.y + 8.0f, static_cast<DirectX::SimpleMath::Color>(DirectX::Colors::Black), 2.0f, m_letter);
	debugFont->draw();
}