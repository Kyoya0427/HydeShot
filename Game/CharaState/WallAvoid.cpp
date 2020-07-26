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

/// <summary>
/// コンストラクタ
/// </summary>
WallAvoid::WallAvoid()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="chara"></param>
void WallAvoid::Initialize(Character* chara, CharacterController* controller)
{
	m_chara = chara;
	
	m_leftward = std::make_unique<Leftward>();
	m_rightward = std::make_unique<Rightward>();

	m_leftward->Initialize(m_chara, m_controller);
	m_rightward->Initialize(m_chara, m_controller);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void WallAvoid::Update(const DX::StepTimer& timer)
{
	float direction = m_chara->GetRadiansY();

	if (direction >= DirectX::XM_PI)
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
