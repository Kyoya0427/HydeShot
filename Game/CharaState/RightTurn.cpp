//======================================================
// File Name	: RightTurn.h
// Summary		: 右回転ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "RightTurn.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
RightTurn::RightTurn()
	: m_chara()
	, m_enemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RightTurn::~RightTurn()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void RightTurn::Initialize(Character* chara, Character* enemy)
{
	m_chara = chara;
	m_enemy = enemy;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void RightTurn::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->RightTurn(AIController::ROT_SPEED);
//	GameContext::Get<Search>()->ChangeStandingState();
}

/// <summary>
/// 描画
/// </summary>
void RightTurn::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"RightTurn");
	debugFont->draw();
}
