//======================================================
// File Name	: Forward.cpp
// Summary		: 前移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "Forward.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/Controller/AIController.h>

#include <Game/GameObject/WallApproach.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Forward::Forward()
	: m_chara()
	, m_enemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Forward::~Forward()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="controller">敵キャラクター</param>
void Forward::Initialize(Character* chara, Character* enemy)
{
	m_chara      = chara;
	m_enemy      = enemy;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Forward::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->Forward(AIController::MOVE_SPEED);
	m_chara->GetWallApproachVel()->SetOffsetAngle(WallApproach::FORWARD_ANGLE);
}

/// <summary>
/// 描画
/// </summary>
void Forward::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 80, static_cast<Color>(Colors::White), 1.0f, L"Forward");
	debugFont->draw();
}
