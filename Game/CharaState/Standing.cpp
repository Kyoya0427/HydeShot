//======================================================
// File Name	: Standing.cpp
// Summary		: 初期ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Standing.h"

#include <Game/Common/DebugFont.h>

#include <Game/CharaState/Search.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Standing::Standing()
	: m_chara()
	, m_enemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Standing::~Standing()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void Standing::Initialize(Character* chara, Character* enemy)
{
	m_chara = chara;
	m_enemy = enemy;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Standing::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void Standing::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, static_cast<Color>(Colors::White), 1.0f, L"Standing");
	debugFont->draw();
}
