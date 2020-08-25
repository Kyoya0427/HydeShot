//======================================================
// File Name	: Button.h
// Summary		: UIボタン
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "Button.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game/Camera/Camera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

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
void Button::Initialize(const Vector2& pos, wchar_t* letter)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());

	m_position = pos;
	m_letter = letter;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Button::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// 描画
/// </summary>
void Button::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	m_spriteBatch->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	if (m_isSelect)
		m_spriteBatch->Draw(m_selectTexture.Get(), m_position);
	else
		m_spriteBatch->Draw(m_defaultTexture.Get(), m_position);
	m_spriteBatch->End();

	debugFont->print(m_position.x + 140.0f, m_position.y + 10.0f, static_cast<Color>(Colors::Black), 2.0f, m_letter);
	debugFont->draw();
}