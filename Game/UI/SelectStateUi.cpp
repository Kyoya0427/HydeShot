//======================================================
// File Name	: InfoWindow.h
// Summary		: 情報ウィンドウ
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "SelectStateUi.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/NeuralNetwork.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
SelectStateUi::SelectStateUi()
{
	m_selectMode  = L"NONE";
	m_selectState = L"NONE";
}

/// <summary>
/// デストラクタ
/// </summary>
SelectStateUi::~SelectStateUi()
{
}

/// <summary>
/// 初期化
/// </summary>
void SelectStateUi::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void SelectStateUi::Update(const DX::StepTimer& timer)
{
}

/// <summary>
/// 描画
/// </summary>
void SelectStateUi::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(10, 350, static_cast<Color>(Colors::White), 1.0f, L" Mode =");
	debugFont->draw();
	debugFont->print(130, 350, static_cast<Color>(Colors::White), 1.0f, m_selectMode);
	debugFont->draw();
	debugFont->print(10, 380, static_cast<Color>(Colors::White), 1.0f, L" State =");
	debugFont->draw();
	debugFont->print(130, 380, static_cast<Color>(Colors::White), 1.0f, m_selectState);
	debugFont->draw();
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">オブジェクト</param>
void SelectStateUi::OnCollision(GameObject* object)
{
}
