//======================================================
// File Name	: UiBg.cpp
// Summary		: �w�i
// Author		: Kyoya  Sakamoto
//======================================================
#include "UiBg.h"

#include <DirectXTK/Effects.h>
#include <DirectXTK/CommonStates.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
UiBg::UiBg()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UiBg::~UiBg()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">���W</param>
void UiBg::Initialize(const DirectX::SimpleMath::Vector3& pos)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\bg01.png", nullptr, m_texture.ReleaseAndGetAddressOf());

	m_position = pos;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void UiBg::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void UiBg::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_position);
	m_spriteBatch->End();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void UiBg::OnCollision(GameObject* object)
{
	object;
}