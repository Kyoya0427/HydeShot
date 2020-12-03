//======================================================
// File Name	: AIController.cpp
// Summary		: �`�h�R���g���[���[
// Author		: Kyoya  Sakamoto
//======================================================
#include "AIController.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>

#include <Game/AI/NeuralNetworkManager.h>

#include <Game/Controller/PlayerController.h>

#include <Game/GameState/PlayState.h>

#include <Game/CharaState/CharaState.h>
#include <Game/CharaState/Attack.h>
#include <Game/CharaState/WallAvoid.h>
#include <Game/CharaState/Search.h>

#include <Game/UI/HpUi.h>
#include <Game/UI/NeuralNetworkData.h>

const float AIController::MOVE_SPEED     = 0.03f;
const float AIController::ROT_SPEED      = 0.01f;
const float AIController::SHOT_INTERVAL  = 0.5f;
const float AIController::STATE_INTERVAL = 0.05f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="character">�R���g���[������I�u�W�F�N�g</param>
/// <param name="enemy">�G�L�����N�^�[</param>
AIController::AIController(Character* character, Character* enemy, SelectMode mode)
	: CharacterController(character)
	, m_neuralNetworkManager()
	, m_enemy()
	, m_state()
	, m_stateInterval()
{
	mode;
	m_enemy = enemy;
	m_shotInterval  = SHOT_INTERVAL;
	m_stateInterval = STATE_INTERVAL;
	m_state = CharaStateID::NONE;
	
	m_search    = std::make_unique<Search>();
	m_attack    = std::make_unique<Attack>();
	m_wallAvoid = std::make_unique<WallAvoid>();

	GameContext::Register<Search>(m_search.get());
	GameContext::Register<WallAvoid>(m_wallAvoid.get());

	ChangeSearchState();

	m_neuralNetworkManager = std::make_unique<NeuralNetworkManager>(m_character, m_enemy);

	//�w�K��������
//	m_neuralNetworkManager->InitializeNeuralNetwork();
	//�w�K��̃f�[�^���g�p
	m_neuralNetworkManager->InputTrainingData(mode);

	m_search->Initialize(m_character, m_enemy, m_neuralNetworkManager.get());
	m_attack->Initialize(m_character, m_enemy, m_neuralNetworkManager.get());
	m_wallAvoid->Initialize(m_character, m_enemy, m_neuralNetworkManager.get());
	
	if (m_character->GetTag() == GameObject::ObjectTag::Enemy1)
	{
		m_character->SetRotation(DirectX::SimpleMath::Vector3(0.0f, 3.15f, 0.0f));
		GameContext::Get<NeuralNetworkData>()->SetNeuralNetwork(m_neuralNetworkManager.get());
	}	

	if (m_character->GetTag() == GameObject::ObjectTag::Enemy2)
		m_character->SetRotation(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AIController::~AIController()
{
}

/// <summary>
/// �X�V	
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void AIController::Update(const DX::StepTimer& timer)
{
	//�J�E���g�_�E��
	m_stateInterval -= float(timer.GetElapsedSeconds());
	m_shotInterval  -= float(timer.GetElapsedSeconds());
	//�C���^�[�o��
	if (m_stateInterval < 0.0f)
	{
		m_state = m_neuralNetworkManager->BehaviorSelection();

		m_stateInterval = STATE_INTERVAL;
	}

	switch (m_state)
	{
	case CharaStateID::ATTACK:
		if (m_shotInterval < 0.0f)
		{
			ChangeAttackState();
			m_shotInterval = SHOT_INTERVAL;
		}
		else
			ChangeSearchState();
		break;
	case CharaStateID::SEARCH:
		ChangeSearchState();
		break;
	case CharaStateID::WALLAVOID:
		ChangeWallAvoidState();
		break;
	}

	m_charaState->Update(timer);	
	if (m_character->GetTag() == GameObject::ObjectTag::Enemy1)
		GameContext::Get<HpUi>()->SetEnemyHp(m_character->GetHp());
	if (m_character->GetTag() == GameObject::ObjectTag::Enemy2)
		GameContext::Get<HpUi>()->SetPlayerHp(m_character->GetHp());
}