//======================================================
// File Name	: PlayerController.cpp
// Summary		: �v���C���[�R���g���[���[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayerController.h"

#include <Game/GameObject/Character.h>

#include <Game/Common/DebugFont.h>

#include <Game/GameState/PlayState.h>
using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayerController::MOVE_SPEED    = 0.05f;
const float PlayerController::ROT_SPEED     = 0.02f;
const float PlayerController::SHOT_INTERVAL = 0.3f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="character">�R���g���[������I�u�W�F�N�g</param>
PlayerController::PlayerController(Character* character)
	: CharacterController(character)
{
	m_shotInterval = SHOT_INTERVAL;
	m_isSaveData   = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerController::~PlayerController()
{
	if(m_isSaveData)
	OutputDataFile("Resources//CSV//InputKey.csv");
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerController::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::State keyState = Keyboard::Get().GetState();

	m_shotInterval -= float(timer.GetElapsedSeconds());
	
	if (keyState.IsKeyDown(Keyboard::Keys::W))
	{
		m_data = InputID::FORWARD;
		m_character->Forward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::S))
	{
		m_data = InputID::BACKWARD;
		m_character->Backward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::A))
	{
		m_data = InputID::LEFTWARD;
		m_character->Leftward(MOVE_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::D))
	{
		m_data = InputID::RIGHTWARD;
		m_character->Rightward(MOVE_SPEED);
	}
	else
	if (keyState.IsKeyDown(Keyboard::Keys::Left))
	{
		m_data = InputID::LEFTWARD;
		m_character->LeftTurn(ROT_SPEED);
	}
	else if (keyState.IsKeyDown(Keyboard::Keys::Right))
	{
		m_data = InputID::RIGHTWARD;
		m_character->RightTurn(ROT_SPEED);
	}
	else
	if (keyState.IsKeyDown(Keyboard::Keys::Space) && m_shotInterval < 0.0f)
	{
		m_data = InputID::SHOOT;
		m_character->Shoot();
		m_shotInterval = SHOT_INTERVAL;
	}
	else
	{
		m_data = InputID::NONE;
	}

	m_outputData.push_back(m_data);
}

/// <summary>
/// ���͂Əo�͂̒l���O���ɏo��
/// </summary>
/// <param name="fname">�o�͂��邽�߂̃t�@�C��</param>
void PlayerController::OutputDataFile(char* fname)
{
	FILE* f;
	errno_t error;
	error = fopen_s(&f, fname, "w");

	for (auto& InputID : m_outputData)
	{
		fprintf(f,"%d \n",static_cast<int>(InputID));
	}
	fclose(f);
}
