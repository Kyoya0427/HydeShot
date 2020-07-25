//======================================================
// File Name	: LeftTurn.h
// Summary		: 左回転ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "LeftTurn.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
LeftTurn::LeftTurn()
{
}

/// <summary>
/// デストラクタ
/// </summary>
LeftTurn::~LeftTurn()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void LeftTurn::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	m_controller = controller;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void LeftTurn::Update(const DX::StepTimer& timer)
{
	m_chara->LeftTurn(AIController::ROT_SPEED);
}

/// <summary>
/// 描画
/// </summary>
void LeftTurn::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"LeftTurn");
	debugFont->draw();
}
