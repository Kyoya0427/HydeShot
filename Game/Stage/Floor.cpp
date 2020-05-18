//======================================================
// File Name	: Floor.cpp
// Summary	: ���N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "pch.h"
#include "Floor.h"
#include "Stage.h"
#include <DirectXTK\CommonStates.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>



Floor::Floor()
	: m_stage(nullptr), m_models{nullptr}, m_state(NONE)
{
}

void Floor::Initialize(Stage * stage, int x, int y)
{
	m_stage = stage;
	m_pos = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
}

void Floor::Update(const DX::StepTimer & timer)
{
	// �_���[�W�t���O�𗎂Ƃ�
	m_damageFlag = false;

	// �_���[�W�ڍs
	if (m_damageTimer > 0.0f)
	{
		float elapsedTime = float(timer.GetElapsedSeconds());

		m_damageTimer -= elapsedTime;
		if (m_damageTimer <= 0.0f)
		{
			m_damageTimer = 0.0f;
			switch (m_state)
			{
			case NORMAL:	// �ʏ�
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

	// ���[���h�s��̍쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	// �_���[�W���������u�Ԃ��烂�f���؂�ւ�����
	State state = m_state;

	// ���f���̕`��
	m_models[state]->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, world
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// ���͔������̉��Z�����i�������ňÂ��Ȃ��Ă��܂��̂Łj
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

