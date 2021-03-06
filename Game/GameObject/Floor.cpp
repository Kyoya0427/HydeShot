//======================================================
// File Name	: Floor.cpp
// Summary		: 床クラス
// Author		: Kyoya  Sakamoto
//======================================================
#include "Floor.h"

#include <Game/Stage/Stage.h>

#include <DirectXTK/CommonStates.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// コンストラクタ
/// </summary>
Floor::Floor()
	: GameObject()
	, m_model()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
void Floor::Initialize(const int x, const int y)
{
	SetPosition(DirectX::SimpleMath::Vector3(static_cast<float>(x), 0.0f, static_cast<float>(y)));
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Floor::Update(const DX::StepTimer & timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
void Floor::Render()
{
	// ワールド行列の作成
	SetWorld(DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition()));

	// ダメージが入った瞬間からモデル切り替えする

	// モデルの描画
	m_model->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, GetWorld()
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// 床は半透明の加算合成（半透明で暗くなってしまうので）
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
	});

}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">オブジェクト</param>
void Floor::OnCollision(GameObject* object)
{
	object;
}