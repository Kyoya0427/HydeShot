#include "pch.h"
#include "Character.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラク
/// </summary>
Character::Character(const ObjectTag tag)
	: IGameObject(tag)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Character::~Character()
{
}

/// <summary>
/// 前進
/// </summary>
/// <param name="speed"></param>
void Character::Forward(Vector3& vel, Vector3& rot, float speed)
{
	vel.z = -speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// 後進
/// </summary>
/// <param name="speed"></param>
void Character::Backward(Vector3& vel, Vector3& rot, float speed)
{
	vel.z = speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// 左に進む
/// </summary>
/// <param name="speed"></param>
void Character::Leftward(Vector3& vel, Vector3& rot, float speed)
{
	vel.x = -speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// 右に進む
/// </summary>
/// <param name="speed"></param>
void Character::Rightward(Vector3& vel, Vector3& rot, float speed)
{
	vel.x = speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// 左に旋回
/// </summary>
/// <param name="speed"></param>
void Character::LeftTurn(Vector3& rot, float speed)
{
	rot.y += speed;
}

/// <summary>
/// 右に旋回
/// </summary>
/// <param name="speed"></param>
void Character::RightTurn(Vector3& rot, float speed)
{
	rot.y -= speed;
}
