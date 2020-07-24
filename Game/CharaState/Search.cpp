//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Search.h"

#include <Game/Common/DebugFont.h>

/// <summary>
/// コンストラクタ
/// </summary>
Search::Search()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void Search::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer"></param>
void Search::Update(const DX::StepTimer& timer)
{
	timer;

}

/// <summary>
/// 描画
/// </summary>
void Search::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"Search");
	debugFont->draw();
}
