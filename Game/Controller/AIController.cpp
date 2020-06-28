//======================================================
// File Name	: AIController.h
// Summary		: ＡＩコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "AIController.h"

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/GameObject/Character.h>

#include <Game/Controller/NeuralNetworkManager.h>
#include <Game/Controller/PlayerController.h>
#include <Game/AI/RuleBased.h>

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float AIController::MOVE_SPEED     = 0.03f;
const float AIController::ROT_SPEED      = 0.01f;
const float AIController::SHOT_INTERVAL  = 0.5f;
const float AIController::STATE_INTERVAL = 0.5f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
AIController::AIController(Character* character, Character* enemy)
	: CharacterController(character)
	, m_stateInterval(0.0f)
	, m_randMobeCount()
{
	m_enemy = enemy;
	m_shotInterval  = SHOT_INTERVAL;
	m_stateInterval = STATE_INTERVAL;
//	m_state = static_cast<Behavior>(rand() % static_cast<int>(Behavior::NUM));
	m_state = Behavior::NONE;
	
//	m_neuralNetworkManager = std::make_unique<NeuralNetworkManager>();

	m_ruleBased = std::make_unique<RuleBased>();

	Vector3 rot = Vector3(0.0f, 3.15f, 0.0f);
	m_character->SetRotation(rot);
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
	m_stateInterval -= float(timer.GetElapsedSeconds());
	m_shotInterval  -= float(timer.GetElapsedSeconds());
	//インターバル
	if (m_stateInterval < 0.0f)
	{
		m_stateInterval = STATE_INTERVAL;

		Vector3 enemy = m_enemy->GetPosition();
		Vector3 aiPos = m_character->GetPosition();
		float x = aiPos.x - enemy.x;
		float z = aiPos.z - enemy.z;

		m_state = m_ruleBased->BehaviorSelection(m_character, m_enemy);
		
		m_randMobeCount++;
		if (m_randMobeCount >= MODE_COUNT)
		{
//			m_state = static_cast<Behavior>(rand() % static_cast<int>(Behavior::NUM));
			m_randMobeCount = 0;
		}
		else
		{
	
//			m_state = m_neuralNetworkManager->BehaviorSelection(x, z, m_character->GetHp());
		}

	}

	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Keys::W))
	{
		m_character->Forward(MOVE_SPEED);
	}
	/*
	else if (keyState.IsKeyDown(Keyboard::Keys::S))
	{
		m_character->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::A))
	{
		m_character->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::D))
	{
		m_character->Rightward(MOVE_SPEED);
	}

	if (keyState.IsKeyDown(Keyboard::Keys::Left))
	{
		m_character->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::Right))
	{
		m_character->RightTurn(ROT_SPEED);
	}

	if (keyState.IsKeyDown(Keyboard::Keys::Space) && m_shotInterval < 0.0f)
	{
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
	}*/
	
	//ステート
	switch (m_state)
	{
	case Behavior::MOVE_FORWARD:
		m_character->Forward(MOVE_SPEED);
		break;
	case Behavior::MOVE_BACKWARD:
		m_character->Backward(MOVE_SPEED);
		break;
	case Behavior::MOVE_LEFTWARD:
		m_character->Leftward(MOVE_SPEED);
		break;
	case Behavior::MOVE_RIGHTWARD:
		m_character->Rightward(MOVE_SPEED);
		break;
	case Behavior::TURN_LEFT:
		m_character->LeftTurn(ROT_SPEED);
		break;
	case Behavior::TURN_RIGHT:
		m_character->RightTurn(ROT_SPEED);
		break;
	case Behavior::SHOOT:
		if (m_shotInterval < 0.0f)
		{
			m_character->Shoot();
			m_shotInterval = SHOT_INTERVAL;
		}
		break;
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
		debugFont->print(10, 30, L"%f / 0.1", m_shotInterval);
		debugFont->draw();
		debugFont->print(10, 50, L"%d", m_randMobeCount);
		debugFont->draw();

		Vector3 enemy = m_enemy->GetPosition();
		Vector3 aiPos = m_character->GetPosition();
		float x = aiPos.x - enemy.x;
		float z = aiPos.z - enemy.z;

		debugFont->print(700, 30, L"X = %f", x);
		debugFont->draw();
		debugFont->print(700, 50, L"Z = %f", z);
		debugFont->draw();


		if (m_character->GetEnemyContact() == true)
		{
			debugFont->print(500, 10, L"true");
			debugFont->draw();
		}
		else
		{
			debugFont->print(500, 10, L"false");
			debugFont->draw();
		}
		wchar_t* state[]
		{
			L"NONE",
			L"FORWARD",
			L"BACKWARD",
			L"LEFTWARD",
			L"RIGHTWARD",
			L"LEFT_TURN",
			L"RIGHT_TURN",
			L"SHOT"
		};
		debugFont->print(10, 10, state[static_cast<int>(m_state)]);
		debugFont->draw();
	}

}