//======================================================
// File Name	: Game.cpp
// Summary	: �Q�[��
// Author		: Kyoya Sakamoto
//======================================================

#include "Game.h"

#include <random>

#include <Game\MyGame.h>

#include <Utils\GameContext.h>
#include <Utils\Projection.h>

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
Game::Game() noexcept(false)
{
	//�f�o�C�X���\�[�V�[�Y�����Ɠo�^
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	GameContext().Register<DX::DeviceResources>(m_deviceResources);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Game::~Game()
{
	
}

/// <summary>
/// ������
/// </summary>
/// <param name="window"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void Game::Initialize(HWND window, int width, int height)
{
	//�E�B���h�E�ݒ�
    m_deviceResources->SetWindow(window, width, height);
    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();
    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// �R�����X�e�[�g�쐬
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
	GameContext().Register<DirectX::CommonStates>(m_state);

	// �}�E�X�̍쐬
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
	//�L�[�{�[�h�̍쐬
	m_keyboard = std::make_unique<Keyboard>();

	m_myGame = std::make_unique<MyGame>();
	m_myGame->Initialize();
	// TODO: �f�t�H���g�ϐ�timestep���[�h�ȊO�̂��̂��K�v�ȏꍇ�^�C�}�[�ݒ��ύX����
	// ��: 60FPS�Œ�^�C���X�e�b�v�X�V���W�b�N�ɑ΂��Ă͈ȉ����Ăяo��

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60.0);
	
}

#pragma region Frame Update
/// <summary>
/// �Q�[�����[�v
/// </summary>
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void Game::Update(DX::StepTimer const& timer)
{
	//�G�X�P�[�v�L�[�ŏI�����鏈��
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Escape))
	{
		ExitGame();
	}

	m_myGame->Update(timer);
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// �`��
/// </summary>
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO:�����艺�ɋL��
    context;

	m_myGame->Render(m_timer);

    m_deviceResources->PIXEndEvent();

    // �V�����t���[����\�����܂��B
    m_deviceResources->Present();
}

// �o�b�N�o�b�t�@�[���N���A����w���p�[���\�b�h
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // �r���[���N���A���܂�
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // �r���[�|�[�g��ݒ肵�܂��B
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// ���b�Z�[�W�n���h���[
void Game::OnActivated()
{
    // TODO: �Q�[���̓A�N�e�B�u�E�B���h�E�ɂȂ����܂��B
}

void Game::OnDeactivated()
{
	// TODO: �Q�[���͔w�i�E�B���h�E�ɂȂ����܂��B
}
void Game::OnSuspending()
{
    // TODO: �Q�[���̓d�����ꎞ��~�i�܂��͍ŏ����j����Ă��܂��B
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: �Q�[���̓d�����ĊJ����Ă��܂��i�܂��͍ŏ������畜�A���Ă��܂��j�B
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: �Q�[���E�B���h�E�̃T�C�Y���ύX����Ă��܂��B
}

// �v���p�e�B
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: �ړI�̃f�t�H���g�̃E�B���h�E�T�C�Y�ɕύX���܂��i�ŏ��T�C�Y��320x200�ł��邱�Ƃɒ��ӂ��Ă��������j�B
    width = 1280;
    height = 720;
}

void Game::ChangeFullscreen(BOOL flag)
{
	m_deviceResources->GetSwapChain()->SetFullscreenState(flag, NULL);
}
#pragma endregion

#pragma region Direct3D Resources
// �����́A�f�o�C�X�Ɉˑ����郊�\�[�X�ł��B
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: �����Ńf�o�C�X�ˑ��I�u�W�F�N�g�����������܂��i�E�B���h�E�T�C�Y�Ɉˑ����܂���j�B
    device;
}

// �E�B���h�E��SizeChanged�C�x���g�ŕύX����邷�ׂẴ��������\�[�X�����蓖�Ă܂��B
void Game::CreateWindowSizeDependentResources()
{
    // TODO: �����ŃE�B���h�E�T�C�Y�Ɉˑ�����I�u�W�F�N�g�����������܂��B

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	
	
}

void Game::OnDeviceLost()
{
    // TODO:������Direct3D���\�[�X�̃N���[���A�b�v��ǉ����܂��B
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
