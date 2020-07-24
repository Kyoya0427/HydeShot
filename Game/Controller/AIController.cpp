//======================================================
// File Name	: AIController.cpp
// Summary		: ＡＩコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "AIController.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>

#include <Game/AI/NeuralNetworkManager.h>
#include <Game/AI/RuleBased.h>

#include <Game/Controller/PlayerController.h>

#include <Game/GameState/PlayState.h>

#include <Game/CharaState/CharaState.h>
#include <Game/CharaState/Attack.h>
#include <Game/CharaState/WallAvoid.h>
#include <Game/CharaState/Search.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float AIController::MOVE_SPEED     = 0.03f;
const float AIController::ROT_SPEED      = 0.01f;
const float AIController::SHOT_INTERVAL  = 0.5f;
const float AIController::STATE_INTERVAL = 0.05f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
AIController::AIController(Character* character, Character* enemy)
	: CharacterController(character)
	, m_aiManager()
	, m_enemy()
	, m_state()
	, m_stateInterval()
{
	m_enemy = enemy;
	m_shotInterval  = SHOT_INTERVAL;
	m_stateInterval = STATE_INTERVAL;
	m_state = State::NONE;
	
	m_search    = std::make_unique<Search>();
	m_attack    = std::make_unique<Attack>();
	m_wallAvoid = std::make_unique<WallAvoid>();

	m_search->Initialize(m_character, this);
	m_attack->Initialize(m_character, this);
	m_wallAvoid->Initialize(m_character, this);

	ChangeSearchState();

	std::unique_ptr<RuleBased> ruleBased = std::make_unique<RuleBased>();
	std::unique_ptr<NeuralNetworkManager> neuralNetworkManager = std::make_unique<NeuralNetworkManager>();
	neuralNetworkManager->InitializeNeuralNetwork();

	m_aiManager.emplace(std::make_pair(AiType::RULEBASED, std::move(ruleBased)));
	m_aiManager.emplace(std::make_pair(AiType::NEURALNETWORK, std::move(neuralNetworkManager)));

	if (m_character->GetTag() == GameObject::ObjectTag::Enemy1)
		m_character->SetRotation(Vector3(0.0f, 3.15f, 0.0f));
	if (m_character->GetTag() == GameObject::ObjectTag::Enemy2)
		m_character->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// デストラクタ
/// </summary>
AIController::~AIController()
{
}

/// <summary>
///　更新	
/// </summary>
/// <param name="timer"></param>
void AIController::Update(const DX::StepTimer& timer)
{
	//カウントダウン
	m_stateInterval -= float(timer.GetElapsedSeconds());
	m_shotInterval  -= float(timer.GetElapsedSeconds());
	//インターバル
	if (m_stateInterval < 0.0f)
	{
		if (m_character->GetTag() == GameObject::ObjectTag::Enemy1)
		m_state = m_aiManager[AiType::NEURALNETWORK]->BehaviorSelection(m_character, m_enemy);
		if (m_character->GetTag() == GameObject::ObjectTag::Enemy2)
			m_state = m_aiManager[AiType::RULEBASED]->BehaviorSelection(m_character, m_enemy);
	
		m_stateInterval = STATE_INTERVAL;

	}
	Keyboard::State keyState = Keyboard::Get().GetState();

	/*if (keyState.IsKeyDown(Keyboard::Keys::I))
	{
		m_character->Forward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::K))
	{
		m_character->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::J))
	{
		m_character->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::L))
	{
		m_character->Rightward(MOVE_SPEED);
	}


	if (keyState.IsKeyDown(Keyboard::Keys::O))
	{
		m_character->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::P))
	{
		m_character->RightTurn(ROT_SPEED);
	}*/

	if (keyState.IsKeyDown(Keyboard::Keys::F1))
	{
		ChangeAttackState();
	}
	if (keyState.IsKeyDown(Keyboard::Keys::F2))
	{
		ChangeSearchState();
	}
	if (keyState.IsKeyDown(Keyboard::Keys::F3))
	{
		ChangeWallAvoidState();
	}
	
}

/// <summary>
/// デバック
/// </summary>
void AIController::Render()
{

	if (PlayState::m_isDebug)
	{
		DebugFont* debugFont = DebugFont::GetInstance();
		debugFont->print(10, 30, L"%f / 0.1", m_stateInterval);
		debugFont->draw();
	

		debugFont->print(700, 30, L"posX = %f", m_enemy->GetPosition().x);
		debugFont->draw();
		debugFont->print(700, 60, L"posY = %f", m_enemy->GetPosition().y);
		debugFont->draw();
		debugFont->print(700, 90, L"posZ = %f", m_enemy->GetPosition().z);
		debugFont->draw();



		m_aiManager[AiType::NEURALNETWORK]->Render();
		m_charaState->Render();
	}

}


/// <summary>
/// 攻撃にステイトを変更
/// </summary>
void AIController::ChangeAttackState()
{
	
	m_charaState = static_cast<CharaState*>(m_attack.get());
}

/// <summary>
/// サーチにステイトを変更
/// </summary>
void AIController::ChangeSearchState()
{
	m_charaState = static_cast<CharaState*>(m_search.get());
}

/// <summary>
/// 壁回避にステイトを変更
/// </summary>
void AIController::ChangeWallAvoidState()
{
	m_charaState = static_cast<CharaState*>(m_wallAvoid.get());
}