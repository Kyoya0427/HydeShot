//======================================================
// File Name	: Bg.cpp
// Summary		: ゲーム背景
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bg.h"

#include <DirectXTK/Effects.h>
#include <DirectXTK/CommonStates.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// コンストラクタ
/// </summary>
Bg::Bg()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Bg::~Bg()
{
}

/// <summary>
/// 初期化
/// </summary>
void Bg::Initialize()
{
	// モデルデータの読み込み
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources//Models");
	m_model = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Models//bg.cmo", fx);

	m_model->UpdateEffects([&](DirectX::IEffect* effect)
	{
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する
			basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Bg::Update(const DX::StepTimer& timer)
{
	timer;
	//回転
	SetRotationY(GetRotation().y + 0.0002f);
}

/// <summary>
/// 描画
/// </summary>
void Bg::Render()
{
	//ワールド行列作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateRotationY(GetRotation().y);
	world       *= DirectX::SimpleMath::Matrix::CreateTranslation(4.5f, -10.0f, 5.5f);
	//ビュー行列作成
	DirectX::SimpleMath::Matrix view  = DirectX::SimpleMath::Matrix::CreateLookAt(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f), DirectX::SimpleMath::Vector3::Up);

	// モデルの描画
	m_model->Draw(
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, view, GameContext::Get<Camera>()->GetProjection());
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Bg::OnCollision(GameObject* object)
{
	object;
}