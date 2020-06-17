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

#include <Game/Controller/MoveModeSelection.h>
#include <Game/Controller/PlayerController.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float AIController::MOVE_SPEED     = 0.01f;
const float AIController::ROT_SPEED      = 0.01f;
const float AIController::SHOT_INTERVAL  = 0.5f;
const float AIController::STATE_INTERVAL = 1.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
AIController::AIController(Character* character)
	: CharacterController(character)
	, m_stateInterval(0.0f)
	, m_state(Behavior::NONE)
{
	m_shotInterval  = SHOT_INTERVAL;
	m_stateInterval = STATE_INTERVAL;
	m_moveModeSelection = std::make_unique<MoveModeSelection>();
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
	m_shotInterval -= float(timer.GetElapsedSeconds());
	//インターバル
	if (m_stateInterval < 0.0f)
	{
		m_stateInterval = STATE_INTERVAL;

		Vector3 playerPos = GameContext::Get<PlayerController>()->GetCharacter()->GetPosition();
		Vector3 aiPos = m_character->GetPosition();

		float x = aiPos.x - playerPos.x;
		float z = aiPos.z - playerPos.z;


		m_state = m_moveModeSelection->BehaviorSelection(x, z, m_character->GetHp());
	}

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
		if(m_shotInterval < 0.0f)
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
		break;
	}

}

/// <summary>
/// デバック
/// </summary>
void AIController::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 30, L"%f / 2.0", m_stateInterval);
	debugFont->draw();

	switch (m_state)
	{
	case Behavior::NONE:
		debugFont->print(10, 10, L"NONE");
		debugFont->draw();
		break;
	case Behavior::MOVE_FORWARD:
		debugFont->print(10, 10, L"FORWARD");
		debugFont->draw();
		break;
	case Behavior::MOVE_BACKWARD:
		debugFont->print(10, 10, L"BACKWARD");
		debugFont->draw();		break;
	case Behavior::MOVE_LEFTWARD:
		debugFont->print(10, 10, L"LEFTWARD");
		debugFont->draw();		break;
	case Behavior::MOVE_RIGHTWARD:
		debugFont->print(10, 10, L"RIGHTWARD");
		debugFont->draw();		break;
	case Behavior::TURN_LEFT:
		debugFont->print(10, 10, L"LEFT_TURN");
		debugFont->draw();		break;
	case Behavior::TURN_RIGHT:
		debugFont->print(10, 10, L"RIGHT_TURN");
		debugFont->draw();		break;
	}

	

	Vector3 playerPos = GameContext::Get<PlayerController>()->GetCharacter()->GetPosition();
	Vector3 aiPos = m_character->GetPosition();
	
	float x = aiPos.x - playerPos.x;
	float z = aiPos.z - playerPos.z;
	debugFont->print(600, 90, L"%f = X", x);
	debugFont->draw();
	debugFont->print(600, 120, L"%f = Z", z);
	debugFont->draw();
	debugFont->print(600, 150, L"%d = HP", m_character->GetHp());
	debugFont->draw();

	m_moveModeSelection->Render();
}
