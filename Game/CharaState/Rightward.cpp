//======================================================
// File Name	: Rightward.h
// Summary		: 右移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Rightward.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
Rightward::Rightward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Rightward::~Rightward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void Rightward::Initialize(Character* chara, CharacterController* controller)
{
	m_chara      = chara;
	m_controller = controller;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Rightward::Update(const DX::StepTimer& timer)
{
	m_chara->Rightward(AIController::MOVE_SPEED);
}

/// <summary>
/// 描画
/// </summary>
void Rightward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Rightward");
	debugFont->draw();
}
