//======================================================
// File Name	: Bg.cpp
// Summary	: �w�i�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Bg.h"

#include <DirectXTK\Effects.h>
#include <DirectXTK\CommonStates.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>

#include <Game\GameWindow\GameWindow.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bg::Bg()
	: m_angle(0.0f)
{
	SetDrawPrio(GameWindow::DRAW_BG);
}

/// <summary>
/// ������
/// </summary>
void Bg::Initialize()
{
	// ���f���f�[�^�̓ǂݍ���
	EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\bg.cmo", fx);

	m_model->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷��
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
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
	m_angle += 0.0002f;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bg::Render(const DX::StepTimer& timer)
{
	timer;
	Matrix world = Matrix::CreateRotationY(m_angle);
	world *= Matrix::CreateTranslation(4.5f, -10.0f, 5.5f);
	Matrix view = Matrix::CreateLookAt(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3::Up);

	// ���f���̕`��
	m_model->Draw(
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
		*GameContext::Get<CommonStates>(),
		world, view, GameContext::Get<Camera>()->GetProjection());
}

void Bg::OnCollision(IGameObject * object)
{
	object;
}
