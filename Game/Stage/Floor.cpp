//======================================================
// File Name	: Floor.cpp
// Summary		: 床クラス
// Date			: 2019/11/28
// Author		: Takafumi Ban
//======================================================

#include "pch.h"
#include "Floor.h"
#include <Game\GameWindow\GameWindow.h>
#include "Stage.h"
#include <DirectXTK\CommonStates.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>



Floor::Floor()
	: m_stage(nullptr), m_models{nullptr}, m_state(NONE)
{
	SetDrawPrio(GameWindow::DRAW_TOP);
}

void Floor::Initialize(Stage * stage, int x, int y)
{
	m_stage = stage;
	m_pos = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
}

void Floor::Update(const DX::StepTimer & timer)
{
	// ダメージフラグを落とす
	m_damageFlag = false;

	// ダメージ移行
	if (m_damageTimer > 0.0f)
	{
		float elapsedTime = float(timer.GetElapsedSeconds());

		m_damageTimer -= elapsedTime;
		if (m_damageTimer <= 0.0f)
		{
			m_damageTimer = 0.0f;
			switch (m_state)
			{
			case NORMAL:	// 通常
				break;
			
			
			default:
				break;
			}
		}
	}

}

void Floor::Render(const DX::StepTimer& timer)
{
	timer;


	if (!m_stage || !m_models[m_state]) return;

	// ワールド行列の作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	// ダメージが入った瞬間からモデル切り替えする
	State state = m_state;

	// モデルの描画
	m_models[state]->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, world
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// 床は半透明の加算合成（半透明で暗くなってしまうので）
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
	});

}

void Floor::OnCollision(IGameObject * object)
{
	object;
}

void Floor::SetModel(State state, DirectX::Model * model)
{
	m_models[state] = model;
}



void Floor::Reset()
{
	m_pos.y = 0.0f;
	if (m_state != Floor::NONE)
	{
		m_state = Floor::NORMAL;
		m_damageFlag = false;
		m_damageTimer = 0.0f;
	}
}

