//======================================================
// File Name	: Floor.cpp
// Summary	: 床クラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Floor.h"
#include "Stage.h"

#include <DirectXTK\CommonStates.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Floor::Floor()
	: m_models{nullptr}
{
}

void Floor::Initialize(int x, int y)
{
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
}

void Floor::Update(const DX::StepTimer & timer)
{
	timer;
}

void Floor::Render(const DX::StepTimer& timer)
{
	timer;




	// ワールド行列の作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// ダメージが入った瞬間からモデル切り替えする

	// モデルの描画
	m_models->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, world
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// 床は半透明の加算合成（半透明で暗くなってしまうので）
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
	});

	

}

void Floor::HitContact(GameObject* object)
{

}

void Floor::SetModel( DirectX::Model * model)
{
	m_models = model;
}







