#include "pch.h"
#include "CharacterController.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N
/// </summary>
CharacterController::CharacterController(const ObjectTag tag)
	: IGameObject(tag)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterController::~CharacterController()
{
}

/// <summary>
/// �O�i
/// </summary>
/// <param name="speed"></param>
void CharacterController::Forward(float speed)
{
	m_velocity.z = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// ��i
/// </summary>
/// <param name="speed"></param>
void CharacterController::Backward(float speed)
{
	m_velocity.z = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// ���ɐi��
/// </summary>
/// <param name="speed"></param>
void CharacterController::Leftward(float speed)
{
	m_velocity.x = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// �E�ɐi��
/// </summary>
/// <param name="speed"></param>
void CharacterController::Rightward(float speed)
{
	m_velocity.x = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// ���ɐ���
/// </summary>
/// <param name="speed"></param>
void CharacterController::LeftTurn(float speed)
{
	m_rotation.y += speed;
}

/// <summary>
/// �E�ɐ���
/// </summary>
/// <param name="speed"></param>
void CharacterController::RightTurn(float speed)
{
	m_rotation.y -= speed;
}
