#include "CharacterController.h"

#include <Game\GameObject\Character.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N
/// </summary>
CharacterController::CharacterController(Character* character)
	: m_character(character)
	, m_shotInterval(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterController::~CharacterController()
{
	m_character = nullptr;
}
