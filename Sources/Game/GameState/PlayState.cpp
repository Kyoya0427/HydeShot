//======================================================
// File Name	: PlayState.h
// Summary	: �v���C�X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================
#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>
#include <SimpleMath.h>

#include <Game\Collider\CollisionManager.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Player\PlayerManager.h>
#include <Game\Player\Player.h>

#include <Game\Stage\StageManager.h>


#include <Utils\GameContext.h>

#include <Framework\DeviceResources.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
	: IGameState()
	, m_collisionManager()
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
	//�f�o�C�X�擾
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//�R���C�_�[�}�l�W���[����
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//���f���t�@�C����w��
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//�X�e�[�W�}�l�[�W���[����
	m_stageManager = std::make_unique<StageManager>();
	m_stageManager->Initialize();

	//TPS�J��������
	m_tpsCamera = std::make_unique<TPSCamera>();
	m_tpsCamera;
	GameContext().Register<TPSCamera>(m_tpsCamera);

	//�v���C���[�}�l�[�W���[����
	m_playerManager = std::make_unique<PlayerManager>();
	m_playerManager->Initialize();
	GameContext().Register<Player>(m_playerManager->GetPlayer());

	
	m_collisionManager->AllowCollision("Player", "Ground");

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	//�|�[�Y���
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	m_stageManager->Update(timer);
	m_tpsCamera->Update(timer);
	m_playerManager->Update(timer);
	m_collisionManager->DetectCollision();
	
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	
	m_stageManager->Render(timer);
	m_playerManager->Render(timer);
	m_tpsCamera->Render(timer);
}

/// <summary>
/// �I��
/// </summary>
void PlayState::Finalize()
{

}
