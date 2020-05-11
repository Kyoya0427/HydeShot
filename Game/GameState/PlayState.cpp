//======================================================
// File Name	: PlayState.h
// Summary	: �v���C�X�e�C�g
//======================================================
#include "PlayState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameState\GameStateManager.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\GameWindow\GameWindow.h>

#include <Game\UI\InfoWindow.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
	: IGameState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayState::~PlayState()
{

}

/// <summary>
/// ������
/// </summary>
void PlayState::Initialize()
{
	// �I�u�W�F�N�g�}�l�[�W���[����
	m_objectManager = std::make_unique<ObjectManager>();
	// ���E�B���h�E��o�^
	GameContext::Register<ObjectManager>(m_objectManager);

	// ���E�B���h�E
	m_infoWindow = std::make_unique<InfoWindow>();
	GameContext::Register<InfoWindow>(m_infoWindow.get());

	//�Q�[���E�B���h�E
	m_gameWindow = std::make_unique<GameWindow>();
	GameContext::Register<GameWindow>(m_gameWindow.get());

	//���E�B���h�E�I�u�W�F�N�g��o�^
	m_objectManager->GetInfoOM()->Add(std::move(m_infoWindow));
	GameContext::Get<InfoWindow>()->Initialize();

	//�Q�[���E�B���h�E�I�u�W�F�N�g��o�^
	m_objectManager->GetGameOM()->Add(std::move(m_gameWindow));
	GameContext::Get<GameWindow>()->Initialize();

	// �r���[�|�[�g�̋�`�̈�̐ݒ�i�Q�[����ʁj
	m_viewportGame = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		static_cast<float>(960),
		static_cast<float>(720)
	);
	// �r���[�|�[�g�̋�`�̈�̐ݒ�i����ʁj
	m_viewportInfo = CD3D11_VIEWPORT(
		static_cast<float>(960),
		0.0f,
		static_cast<float>(320),
		static_cast<float>(720)
	);

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();
	
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::RESULT_STATE);
	}

	ChangePauseState();
	// �Q�[����ʂ̃I�u�W�F�N�g�X�V
	m_objectManager->GetGameOM()->Update(timer);
	// ����ʂ̃I�u�W�F�N�g�X�V
	m_objectManager->GetInfoOM()->Update(timer);

	


}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	timer;
	DeviceResources* deviceResources = GameContext::Get<DeviceResources>();
	SpriteBatch* spriteBach = GameContext::Get<SpriteBatch>();
	CommonStates* state = GameContext::Get<CommonStates>();
	auto context = deviceResources->GetD3DDeviceContext();

	// �r���[�|�[�g��ύX����i�����֕`��G���A��ύX����j
	context->RSSetViewports(1, &m_viewportGame);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// TODO: �r���[�s��ƃv���W�F�N�V�����s���ݒ�
	SimpleMath::Matrix viewMat, projMat;
	// �Q�[����ʂ̃I�u�W�F�N�g�`��


	m_objectManager->GetGameOM()->Render(timer);
	spriteBach->End(); // <---�X�v���C�g�̕`��͂����ł܂Ƃ߂čs���Ă���


	// �r���[�|�[�g��ύX����i�E���֕`��G���A��ύX����j
	context->RSSetViewports(1, &m_viewportInfo);

	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// ����ʂ̃I�u�W�F�N�g�`��
	m_objectManager->GetInfoOM()->Render(timer);
	spriteBach->End(); // <---�X�v���C�g�̕`��͂����ł܂Ƃ߂čs���Ă���

	auto viewport = deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	
}

/// <summary>
/// �I��
/// </summary>
void PlayState::Finalize()
{
	GameContext::Reset<ObjectManager>();
	GameContext().Reset<GameWindow>();
	GameContext().Reset<InfoWindow>();
	m_objectManager.reset();
}

void PlayState::ChangePauseState()
{
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Escape))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PAUSE_STATE);
	}
}
