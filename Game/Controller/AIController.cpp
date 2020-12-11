//======================================================
// File Name	: AIController.cpp
// Summary		: ＡＩコントローラー
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
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
/// <param name="enemy">敵キャラクター</param>
AIController::AIController(Character* character, Character* enemy, SelectMode mode)
	: CharacterController(character)
	, m_neuralNetworkManager()
	, m_enemy()
	, m_state()
	, m_stateInterval()
{
	mode;
	m_enemy = enemy;
	SetShotInterval(SHOT_INTERVAL);
	m_stateInterval = STATE_INTERVAL;
	m_state = CharaStateID::NONE;
	
	m_search    = std::make_unique<Search>();
	m_attack    = std::make_unique<Attack>();
	m_wallAvoid = std::make_unique<WallAvoid>();

	GameContext::Register<Search>(m_search.get());
	GameContext::Register<WallAvoid>(m_wallAvoid.get());

	ChangeSearchState();

	m_neuralNetworkManager = std::make_unique<NeuralNetworkManager>(GetCharacter(), m_enemy);

	//学習をさせる
//	m_neuralNetworkManager->InitializeNeuralNetwork();
	//学習後のデータを使用
	m_neuralNetworkManager->InputTrainingData(mode);

	m_search->Initialize(GetCharacter(), m_enemy, m_neuralNetworkManager.get());
	m_attack->Initialize(GetCharacter(), m_enemy, m_neuralNetworkManager.get());
	m_wallAvoid->Initialize(GetCharacter(), m_enemy, m_neuralNetworkManager.get());
	
	if (GetCharacter()->GetTag() == GameObject::ObjectTag::Enemy1)
	{
		GetCharacter()->SetRotation(DirectX::SimpleMath::Vector3(0.0f, 3.15f, 0.0f));
		GameContext::Get<NeuralNetworkData>()->SetNeuralNetwork(m_neuralNetworkManager.get());
	}	

	if (GetCharacter()->GetTag() == GameObject::ObjectTag::Enemy2)
		GetCharacter()->SetRotation(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// デストラクタ
/// </summary>
AIController::~AIController()
{
}

/// <summary>
/// 更新	
/// </summary>
/// <param name="timer">タイマー</param>
void AIController::Update(const DX::StepTimer& timer)
{
	//カウントダウン
	m_stateInterval -= static_cast<float>(timer.GetElapsedSeconds());
	SetShotInterval(GetShotInterval() - static_cast<float>(timer.GetElapsedSeconds()));
	//インターバル
	if (m_stateInterval < 0.0f)
	{
		m_state = m_neuralNetworkManager->BehaviorSelection();

		m_stateInterval = STATE_INTERVAL;
	}

	switch (m_state)
	{
	case CharaStateID::ATTACK:
		if (GetShotInterval() < 0.0f)
		{
			ChangeAttackState();
			SetShotInterval(SHOT_INTERVAL);
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

	GetCharaState()->Update(timer);	
	if (GetCharacter()->GetTag() == GameObject::ObjectTag::Enemy1)
		GameContext::Get<HpUi>()->SetEnemyHp(GetCharacter()->GetHp());
	if (GetCharacter()->GetTag() == GameObject::ObjectTag::Enemy2)
		GameContext::Get<HpUi>()->SetPlayerHp(GetCharacter()->GetHp());
}