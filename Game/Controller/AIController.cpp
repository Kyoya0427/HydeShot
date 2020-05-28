//======================================================
// File Name	: AIController.h
// Summary	: ＡＩコントローラー
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "AIController.h"

#include <Game\Common\DebugFont.h>

#include <Game\GameObject\Character.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;

const float AIController::MOVE_SPEED = 0.01f;
const float AIController::ROT_SPEED  = 0.1f;

/// <summary>
/// コンストラク
/// </summary>
AIController::AIController(Character* character)
	: CharacterController(character)
	, m_interval(0.0f)
	, m_state(Behavior::NONE)

{
	
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
	m_interval += float(timer.GetElapsedSeconds());
	m_shotInterval += float(timer.GetElapsedSeconds());

	//インターバル
	if (m_interval >= 2.0f)
	{
		m_interval = 0.0f;
		m_state = static_cast<Behavior>(rand() % static_cast<int>(Behavior::NUM));
	}

	if (m_shotInterval >= 0.3f)
	{
		m_shotInterval = 0.0f;
		m_character->Shooting();
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
	}

}

/// <summary>
/// デバック
/// </summary>
void AIController::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 30, L"%f / 2.0", m_interval);
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

}
