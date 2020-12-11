//======================================================
// File Name	: ResultBg.cpp
// Summary		: ���U���g�w�i
// Author		: Kyoya  Sakamoto
//======================================================
#include "ResultBg.h"

#include <DirectXTK/Effects.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/Camera/Camera.h>

#include <Game/GameState/ResultState.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultBg::ResultBg()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultBg::~ResultBg()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="pos">�Z���^�[���W</param>
void ResultBg::Initialize(const DirectX::SimpleMath::Vector3& pos)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//playerWin.png", NULL, m_winTexture.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources//Textures//youLose.png", NULL, m_loseTexture.ReleaseAndGetAddressOf());
	SetPosition(pos);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ResultBg::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void ResultBg::Render()
{
	m_spriteBatch->Begin();
	if (ResultState::m_isPlayerWin)
		m_spriteBatch->Draw(m_winTexture.Get(), GetPosition());
	else
		m_spriteBatch->Draw(m_loseTexture.Get(), GetPosition());

	m_spriteBatch->End();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void ResultBg::OnCollision(GameObject* object)
{
	object;
}