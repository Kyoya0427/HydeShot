//======================================================
// File Name	: Leftward.h
// Summary		: 左移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Leftward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

/// <summary>
/// コンストラクタ
/// </summary>
Leftward::Leftward()
	: m_chara()
	, m_enemy()
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
void Leftward::Initialize(Character* chara, Character* enemy)
{
	m_chara      = chara;
	m_enemy      = enemy;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Leftward::Update(const DX::StepTimer& timer)
{
	timer;
	float direction = m_chara->GetRadiansY();

	if (direction > DirectX::XM_PI)
		GameContext::Get<WallAvoid>()->ChangeRightwardState();

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
