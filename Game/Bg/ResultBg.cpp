//======================================================
// File Name	: ResultBg.cpp
// Summary		: リザルト背景
// Author		: Kyoya  Sakamoto
//======================================================
#include "ResultBg.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

#include <Game/GameState/ResultState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
ResultBg::ResultBg()
{

}

/// <summary>
/// デストラクタ
/// </summary>
ResultBg::~ResultBg()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">センター座標</param>
void ResultBg::Initialize(const Vector3& pos)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//playerWin.png", NULL, m_winTexture.ReleaseAndGetAddressOf());
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//youLose.png", NULL, m_loseTexture.ReleaseAndGetAddressOf());
	m_position = pos;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void ResultBg::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void ResultBg::Render()
{
	m_spriteBatch->Begin();
	if (ResultState::m_isPlayerWin)
		m_spriteBatch->Draw(m_winTexture.Get(), m_position);
	else
		m_spriteBatch->Draw(m_loseTexture.Get(), m_position);

	m_spriteBatch->End();
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void ResultBg::OnCollision(GameObject* object)
{
	object;
}