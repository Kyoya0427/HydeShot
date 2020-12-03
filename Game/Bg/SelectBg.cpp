//======================================================
// File Name	: SelectBg.cpp
// Summary		: �w�i
// Author		: Kyoya  Sakamoto
//======================================================
#include "SelectBg.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectBg::SelectBg()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectBg::~SelectBg()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�Z���^�[���W</param>
void SelectBg::Initialize(const DirectX::SimpleMath::Vector3& pos)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//select.png", NULL, m_texture.ReleaseAndGetAddressOf());
	m_position = pos;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void SelectBg::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void SelectBg::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_position);
	m_spriteBatch->End();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void SelectBg::OnCollision(GameObject* object)
{
	object;
}