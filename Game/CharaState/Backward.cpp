//======================================================
// File Name	: Backward.h
// Summary		: 後ろ移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Backward.h"

#include <Game/Common/DebugFont.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
Backward::Backward()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Backward::~Backward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">コントローラー</param>
void Backward::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	m_controller = controller;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Backward::Update(const DX::StepTimer& timer)
{
	m_chara->Backward(AIController::MOVE_SPEED);
}

/// <summary>
/// 描画
/// </summary>
void Backward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, L"Backward");
	debugFont->draw();
}
