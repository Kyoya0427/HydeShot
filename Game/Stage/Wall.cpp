//======================================================
// File Name	: Wall.cpp
// Summary	: 壁クラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Wall.h"
#include "Stage.h"

#include <DirectXTK\CommonStates.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\BoxCollider.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Wall::Wall()
	: m_models{nullptr}
{
}

void Wall::Initialize(int x, int y)
{
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
	m_color = Colors::Yellow;
	
	m_collSize = Vector3(0.5f, 0.5f, 0.5f);
//	m_collSize = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 size = Vector3(1.0f, 1.0f, 1.0f);
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_boxCollider = GeometricPrimitive::CreateBox(deviceContext, size);

	m_collider = std::make_unique<BoxCollider>(this, m_collSize);
	m_collider->SetSize(m_collSize);
	GameContext().Get<CollisionManager>()->Add("Wall", m_collider.get());
}

void Wall::Update(const DX::StepTimer & timer)
{
	timer;
	GameContext().Get<CollisionManager>()->Add("Wall", m_collider.get());

}

void Wall::Render()
{
	// ワールド行列の作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

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


		Matrix transMat = Matrix::CreateTranslation(m_position);
		Matrix scalemat = Matrix::CreateScale(m_scale);

		Matrix worldSphere = scalemat * transMat;

		m_boxCollider->Draw(worldSphere, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);
	

}

void Wall::HitContact(GameObject* object)
{
	object;
}

void Wall::SetModel(DirectX::Model * model)
{
	m_models = model;
}

DirectX::SimpleMath::Vector3 Wall::GetCollSize()
{
	return m_collSize;
}





