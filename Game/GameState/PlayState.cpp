//======================================================
// File Name	: PlayState.h
// Summary	: �v���C�X�e�C�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\Camera\Camera.h>

#include <Game\Stage\Stage.h>
#include <Game\Stage\Floor.h>

#include <Game\Bg\Bg.h>

#include <Game\UI\InfoWindow.h>

#include <Game\GameObject\Character.h>

#include <Game\Controller\PlayerController.h>
#include <Game\Controller\AIController.h>

#include <Game\ArtilleryShell\ArtilleryShell.h>

#include <Game\Collider\CollisionManager.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
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
	//�J�����𐶐�
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());
	//�R���C�_�[�}�l�W���[����
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	m_collisionManager->AllowCollision("Character", "Wall");
	m_collisionManager->AllowCollision("Shell", "Wall");

	//�X�e�[�W�𐶐�
	m_stage = std::make_unique<Stage>();
	
	// �X�e�[�W�f�[�^�̓ǂݍ���
	m_stage->LoadStageData(L"Resources\\StageData\\Stage01.csv");
	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();
	m_stage->Initialize();
	GameContext::Register<Stage>(m_stage.get());
	//�v���C���[
	m_player = std::make_unique<Character>(GameObject::Player);
	m_player->Initialize(m_stage->GetPlayerPos());
	m_player->SetColor(Color(Colors::Red));

	m_playerController = std::make_unique<PlayerController>(m_player.get());
	//�G�l�~�[
	m_enemy = std::make_unique<Character>(GameObject::Enemy);
	Vector2 pos = Vector2(8, 8);
	m_enemy->Initialize(pos);
//	m_enemy->Initialize(m_stage->GetEnemyPos());

	m_enemy->SetColor(Color(Colors::Blue));
	m_aiController = std::make_unique<AIController>(m_enemy.get());




	// ���E�B���h�E
	m_infoWindow = std::make_unique<InfoWindow>();
	m_infoWindow->Initialize();
	GameContext::Register<InfoWindow>(m_infoWindow.get());


	//�Q�[���E�B���h�E
	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	



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
	m_bg->Update(timer);
	m_infoWindow->Update(timer);
	// �Q�[����ʂ̃I�u�W�F�N�g�X�V
	m_objectManager->GetGameOM()->Update(timer);


	m_playerController->Update(timer);
	m_aiController->Update(timer);

	m_player->Update(timer);
	m_enemy->Update(timer);

	m_collisionManager->DetectCollision();
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
	m_bg->Render(timer);
	// �Q�[����ʂ̃I�u�W�F�N�g�`��
	m_objectManager->GetGameOM()->Render(timer);
	m_aiController->Render();
	m_playerController->Render();
	m_player->Render(timer);
	m_enemy->Render(timer);

	
	spriteBach->End(); // <---�X�v���C�g�̕`��͂����ł܂Ƃ߂čs���Ă���


	// �r���[�|�[�g��ύX����i�E���֕`��G���A��ύX����j
	context->RSSetViewports(1, &m_viewportInfo);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());

	// ����ʂ̃I�u�W�F�N�g�`��
	m_infoWindow->Render(timer);
	
	spriteBach->End(); // <---�X�v���C�g�̕`��͂����ł܂Ƃ߂čs���Ă���

	auto viewport = deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	
}

/// <summary>
/// �I��
/// </summary>
void PlayState::Finalize()
{
	GameContext().Reset<InfoWindow>();
}

