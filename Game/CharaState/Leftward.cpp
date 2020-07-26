//======================================================
// File Name	: Leftward.h
// Summary		: 左移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Leftward.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
Leftward::Leftward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Leftward::~Leftward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void Leftward::Initialize(Character* chara, CharacterController* controller)
{
	m_chara      = chara;
	m_controller = controller;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Leftward::Update(const DX::StepTimer& timer)
{
	m_chara->Leftward(AIController::MOVE_SPEED);
}

/// <summary>
/// 描画
/// </summary>
void Leftward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Leftward");
	debugFont->draw();
}
