//======================================================
// File Name	: AutoPlayerController.cpp
// Summary		: プレイヤーコントローラー
// Author		: Kyoya  Sakamoto
//======================================================
#include "AutoPlayerController.h"

#include <fstream>
#include <sstream>
#include <string>

#include <Game/GameObject/Character.h>

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>

#include <Game/GameState/PlayState.h>
#include <Game/GameState/GameStateManager.h>

#include <Game/UI/HpUi.h>

const float AutoPlayerController::MOVE_SPEED    = 0.05f;
const float AutoPlayerController::ROT_SPEED     = 0.02f;
const float AutoPlayerController::SHOT_INTERVAL = 0.3f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="character">コントロールするオブジェクト</param>
AutoPlayerController::AutoPlayerController(Character* character)
	: CharacterController(character)
{
	SetShotInterval(SHOT_INTERVAL);
	m_isSaveData = false;
	m_count = 0;
	InitializeTraining(L"Resources//CSV//InputKey.csv");
}

/// <summary>
/// デストラクタ
/// </summary>
AutoPlayerController::~AutoPlayerController()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void AutoPlayerController::Update(const DX::StepTimer& timer)
{
	timer;

	if (m_count >= MAX_DATA - 1)
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}

	switch (static_cast<InputID>(m_data[m_count]))
	{
	case InputID::NONE:
		break;
	case InputID::FORWARD:
		GetCharacter()->Forward(MOVE_SPEED);
		break;
	case InputID::BACKWARD:
		GetCharacter()->Backward(MOVE_SPEED);
		break;
	case InputID::LEFTWARD:
		GetCharacter()->Leftward(MOVE_SPEED);
		break;
	case InputID::RIGHTWARD:
		GetCharacter()->Rightward(MOVE_SPEED);
		break;
	case InputID::LEFT_TURN:
		GetCharacter()->LeftTurn(ROT_SPEED);
		break;
	case InputID::RIGHT_TURN:
		GetCharacter()->RightTurn(ROT_SPEED);
		break;
	case InputID::SHOOT:
		GetCharacter()->Shoot();
		SetShotInterval(SHOT_INTERVAL);
		break;

	default:
		GetCharacter()->Shoot();
		SetShotInterval(SHOT_INTERVAL);
		break;
	}

	m_count++;
	GameContext::Get<HpUi>()->SetPlayerHp(GetCharacter()->GetHp());
}

/// <summary>
/// データを取得
/// </summary>
/// <param name="fname">ファイルネーム</param>
void AutoPlayerController::InitializeTraining(wchar_t* fname)
{
	std::wstring str;
	// ファイルのオープン
	std::wifstream ifs(fname);

	m_data = std::vector<int>(MAX_DATA, 1);

	// ステージデータの読み込み
	
	for (int i = 0; i < MAX_DATA; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		std::getline(stream, tmp, L',');
		m_data[i] = std::stoi(tmp);
	}
}