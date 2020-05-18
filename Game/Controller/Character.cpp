#include "pch.h"
#include "Character.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N
/// </summary>
Character::Character(const ObjectTag tag)
	: IGameObject(tag)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Character::~Character()
{
}

/// <summary>
/// �O�i
/// </summary>
/// <param name="speed"></param>
void Character::Forward(Vector3& vel, Vector3& rot, float speed)
{
	vel.z = -speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// ��i
/// </summary>
/// <param name="speed"></param>
void Character::Backward(Vector3& vel, Vector3& rot, float speed)
{
	vel.z = speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// ���ɐi��
/// </summary>
/// <param name="speed"></param>
void Character::Leftward(Vector3& vel, Vector3& rot, float speed)
{
	vel.x = -speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// �E�ɐi��
/// </summary>
/// <param name="speed"></param>
void Character::Rightward(Vector3& vel, Vector3& rot, float speed)
{
	vel.x = speed;
	Quaternion quaternion = Quaternion::CreateFromAxisAngle(Vector3::UnitY, rot.y);
	vel = Vector3::Transform(vel, quaternion);
}

/// <summary>
/// ���ɐ���
/// </summary>
/// <param name="speed"></param>
void Character::LeftTurn(Vector3& rot, float speed)
{
	rot.y += speed;
}

/// <summary>
/// �E�ɐ���
/// </summary>
/// <param name="speed"></param>
void Character::RightTurn(Vector3& rot, float speed)
{
	rot.y -= speed;
}
