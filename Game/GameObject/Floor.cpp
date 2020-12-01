//======================================================
// File Name	: Floor.cpp
// Summary		: ���N���X
// Author		: Kyoya  Sakamoto
//======================================================
#include "Floor.h"

#include <Game/Stage/Stage.h>

#include <DirectXTK/CommonStates.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Floor::Floor()
	: GameObject()
	, m_model()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="x">x���W</param>
/// <param name="y">y���W</param>
void Floor::Initialize(const int x, const int y)
{
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Floor::Update(const DX::StepTimer & timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void Floor::Render()
{
	// ���[���h�s��̍쐬
	m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// �_���[�W���������u�Ԃ��烂�f���؂�ւ�����

	// ���f���̕`��
	m_model->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, m_world
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// ���͔������̉��Z�����i�������ňÂ��Ȃ��Ă��܂��̂Łj
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
	});

}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void Floor::OnCollision(GameObject* object)
{
	object;
}