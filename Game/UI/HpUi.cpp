//======================================================
// File Name	: HpUi.cpp
// Summary		: ニューラルネットワークの情報
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "HpUi.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
HpUi::HpUi()
	: m_playerHp()
	, m_enemyHp()
{
}

/// <summary>
/// デストラクタ
/// </summary>
HpUi::~HpUi()
{
}

/// <summary>
/// 初期化
/// </summary>
void HpUi::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void HpUi::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void HpUi::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(30, 500, static_cast<Color>(Colors::White), 1.3f, L"Player = %d", m_playerHp);
	debugFont->draw();

	debugFont->print(30, 530, static_cast<Color>(Colors::White), 1.3f, L"Enemy = %d", m_enemyHp);
	debugFont->draw();
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">オブジェクト</param>
void HpUi::OnCollision(GameObject* object)
{
	object;
}