//======================================================
// File Name	: Leftward.cpp
// Summary		: 左移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Leftward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

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
/// <param name="controller">敵キャラクター</param>
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
	m_chara->Leftward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::LEFT_ANGLE);
}

/// <summary>
/// 描画
/// </summary>
void Leftward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, static_cast<Color>(Colors::White), 1.0f, L"Leftward");
	debugFont->draw();
}
