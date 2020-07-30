//======================================================
// File Name	: WallAvoid.h
// Summary		: 壁回避ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallAvoid.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
WallAvoid::WallAvoid()
	: m_chara()
	, m_enemy()
	, m_wallAvoid()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void WallAvoid::Initialize(Character* chara, Character* enemy)
{
	m_chara = chara;
	m_enemy = enemy;
	m_leftward = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_leftward->Initialize(m_chara, m_enemy);
	m_rightward->Initialize(m_chara, m_enemy);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
	float z = m_chara->GetPosition().x - m_enemy->GetPosition().x;
	
	if (z < 0.0f)
		ChangeLeftwardState();
	else
		ChangeRightwardState();

	m_wallAvoid->Update(timer);
}


/// <summary>
/// 描画
/// </summary>
void WallAvoid::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 50, L"WallAvoid");
	debugFont->draw();
	m_wallAvoid->Render();
}

/// <summary>
/// Leftwardに変更
/// </summary>
void WallAvoid::ChangeLeftwardState()
{
	m_wallAvoid = static_cast<CharaState*>(m_leftward.get());
}

/// <summary>
/// Rightwardに変更
/// </summary>
void WallAvoid::ChangeRightwardState()
{
	m_wallAvoid = static_cast<CharaState*>(m_rightward.get());
}
