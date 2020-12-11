//======================================================
// File Name	: Bg.cpp
// Summary		: �Q�[���w�i
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bg.h"

#include <DirectXTK/Effects.h>
#include <DirectXTK/CommonStates.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bg::Bg()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bg::~Bg()
{
}

/// <summary>
/// ������
/// </summary>
void Bg::Initialize()
{
	// ���f���f�[�^�̓ǂݍ���
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources//Models");
	m_model = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Models//bg.cmo", fx);

	m_model->UpdateEffects([&](DirectX::IEffect* effect)
	{
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷��
			basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bg::Update(const DX::StepTimer& timer)
{
	timer;
	//��]
	SetRotationY(GetRotation().y + 0.0002f);
}

/// <summary>
/// �`��
/// </summary>
void Bg::Render()
{
	//���[���h�s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateRotationY(GetRotation().y);
	world       *= DirectX::SimpleMath::Matrix::CreateTranslation(4.5f, -10.0f, 5.5f);
	//�r���[�s��쐬
	DirectX::SimpleMath::Matrix view  = DirectX::SimpleMath::Matrix::CreateLookAt(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f), DirectX::SimpleMath::Vector3(0.0f, 0.0f, -1.0f), DirectX::SimpleMath::Vector3::Up);

	// ���f���̕`��
	m_model->Draw(
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, view, GameContext::Get<Camera>()->GetProjection());
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Bg::OnCollision(GameObject* object)
{
	object;
}