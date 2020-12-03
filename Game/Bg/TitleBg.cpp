//======================================================
// File Name	: TitleBg.cpp
// Summary		: 背景
// Author		: Kyoya  Sakamoto
//======================================================
#include "TitleBg.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// コンストラクタ
/// </summary>
TitleBg::TitleBg()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleBg::~TitleBg()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="pos">センター座標</param>
void TitleBg::Initialize(const DirectX::SimpleMath::Vector3& pos)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//title.png", NULL, m_texture.ReleaseAndGetAddressOf());

	m_position = pos;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void TitleBg::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void TitleBg::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_position);
	m_spriteBatch->End();
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void TitleBg::OnCollision(GameObject* object)
{
	object;
}