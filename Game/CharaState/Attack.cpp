//======================================================
// File Name	: Attack.h
// Summary		: 攻撃ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Attack.h"

#include <Game/Common/DebugFont.h>

/// <summary>
/// コンストラクタ
/// </summary>
Attack::Attack()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void Attack::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Attack::Update(const DX::StepTimer& timer)
{
	m_chara->Shoot();

}

/// <summary>
/// 描画
/// </summary>
void Attack::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"Attack");
	debugFont->draw();
}
