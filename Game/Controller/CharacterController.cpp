#include "pch.h"
#include "CharacterController.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラク
/// </summary>
CharacterController::CharacterController(const ObjectTag tag)
	: IGameObject(tag)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CharacterController::~CharacterController()
{
}

/// <summary>
/// 前進
/// </summary>
/// <param name="speed"></param>
void CharacterController::Forward(float speed)
{
	m_velocity.z = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// 後進
/// </summary>
/// <param name="speed"></param>
void CharacterController::Backward(float speed)
{
	m_velocity.z = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// 左に進む
/// </summary>
/// <param name="speed"></param>
void CharacterController::Leftward(float speed)
{
	m_velocity.x = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// 右に進む
/// </summary>
/// <param name="speed"></param>
void CharacterController::Rightward(float speed)
{
	m_velocity.x = speed;
	Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_rotation.y);
	m_velocity = Vector3::Transform(m_velocity, rot);
}

/// <summary>
/// 左に旋回
/// </summary>
/// <param name="speed"></param>
void CharacterController::LeftTurn(float speed)
{
	m_rotation.y += speed;
}

/// <summary>
/// 右に旋回
/// </summary>
/// <param name="speed"></param>
void CharacterController::RightTurn(float speed)
{
	m_rotation.y -= speed;
}
