//======================================================
// File Name	: AutoPlayerController.cpp
// Summary		: �v���C���[�R���g���[���[
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
/// �R���X�g���N�^
/// </summary>
/// <param name="character">�R���g���[������I�u�W�F�N�g</param>
AutoPlayerController::AutoPlayerController(Character* character)
	: CharacterController(character)
{
	m_shotInterval = SHOT_INTERVAL;
	m_isSaveData = false;
	m_count = 0;
	InitializeTraining(L"Resources//CSV//InputKey.csv");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AutoPlayerController::~AutoPlayerController()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
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
		m_character->Forward(MOVE_SPEED);
		break;
	case InputID::BACKWARD:
		m_character->Backward(MOVE_SPEED);
		break;
	case InputID::LEFTWARD:
		m_character->Leftward(MOVE_SPEED);
		break;
	case InputID::RIGHTWARD:
		m_character->Rightward(MOVE_SPEED);
		break;
	case InputID::LEFT_TURN:
		m_character->LeftTurn(ROT_SPEED);
		break;
	case InputID::RIGHT_TURN:
		m_character->RightTurn(ROT_SPEED);
		break;
	case InputID::SHOOT:
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
		break;

	default:
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
		break;
	}

	m_count++;
	GameContext::Get<HpUi>()->SetPlayerHp(m_character->GetHp());
}

/// <summary>
/// �f�[�^���擾
/// </summary>
/// <param name="fname">�t�@�C���l�[��</param>
void AutoPlayerController::InitializeTraining(wchar_t* fname)
{
	std::wstring str;
	// �t�@�C���̃I�[�v��
	std::wifstream ifs(fname);

	m_data = std::vector<int>(MAX_DATA, 1);

	// �X�e�[�W�f�[�^�̓ǂݍ���
	
	for (int i = 0; i < MAX_DATA; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		std::getline(stream, tmp, L',');
		m_data[i] = std::stoi(tmp);
	}
}