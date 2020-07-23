//======================================================
// File Name	: WallAvoid.h
// Summary		: 壁回避ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>

/// <summary>
/// コンストラクタ
/// </summary>
WallAvoid::WallAvoid()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void WallAvoid::Initialize(Character* chara)
{
	m_chara = chara;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// 描画
/// </summary>
void WallAvoid::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"WallAvoid");
	debugFont->draw();
}
