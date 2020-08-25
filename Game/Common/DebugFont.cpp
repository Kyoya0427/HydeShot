//======================================================
// File Name	: DebugFont.h
// Summary		: デバックフォント
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "DebugFont.h"

#if DEBUG_FONT_SINGLETON_TYPE == 0
DebugFont* DebugFont::m_pInstance = nullptr;
#elif DEBUG_FONT_SINGLETON_TYPE == 1
std::unique_ptr<DebugFont> DebugFont::m_pInstance = nullptr;
#else
DebugFont DebugFont::m_instance;
#endif

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
DebugFont::DebugFont()
	: m_pos(0, 0)
	, m_color()
	, m_string(nullptr)
	, m_fontSize()
{
	m_string = new wchar_t[STRING_SIZE_MAX];
}

/// <summary>
/// デストラクタ
/// </summary>
DebugFont::~DebugFont()
{
	delete[] m_string;
}

/// <summary>
/// 生成
/// </summary>
/// <param name="device"></param>
/// <param name="context"></param>
void DebugFont::create(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

/// <summary>
/// 描画
/// </summary>
void DebugFont::draw()
{
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), m_string, m_pos, m_color, 0.0f, Vector2::Zero, m_fontSize);
	m_spriteBatch->End();
}

/// <summary>
/// リセット
/// </summary>
void DebugFont::reset()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}

/// <summary>
/// 表示情報登録
/// </summary>
void DebugFont::print(float posX, float posY, DirectX::SimpleMath::Color color, float fontSize, wchar_t const* const format, ...)
{
	m_pos.x = posX;
	m_pos.y = posY;
	m_color = color;
	m_fontSize = fontSize;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}

/// <summary>
/// 表示情報登録（Vector2版）
/// </summary>
void DebugFont::print(const DirectX::SimpleMath::Vector2& pos, DirectX::SimpleMath::Color color, float fontSize, wchar_t const* const format, ...)
{
	m_pos = pos;
	m_color = color;
	m_color = color;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}