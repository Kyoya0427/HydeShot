//======================================================
// File Name	: Attack.cpp
// Summary		: 攻撃ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Attack::Attack()
	: m_chara()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="enemy">敵キャラクター</param>
void Attack::Initialize(Character* chara, Character* enemy)
{
	enemy;
	m_chara = chara;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Attack::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Shoot();
}

/// <summary>
/// 描画
/// </summary>
void Attack::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, static_cast<Color>(Colors::White), 1.0f, L"Attack");
	debugFont->draw();
}
