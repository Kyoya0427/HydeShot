//======================================================
// File Name	: GameObject.cpp
// Summary		: �Q�[���I�u�W�F�N�g
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�^�O��</param>
GameObject::GameObject(const ObjectTag tag)
	: m_tag(tag)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_color(0.0f, 0.0f, 0.0f,0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// ����
/// </summary>
void GameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// �L��
/// </summary>
/// <returns></returns>
bool GameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// ����
/// </summary>
/// <returns></returns>
bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// �^�O���擾
/// </summary>
/// <returns></returns>
const GameObject::ObjectTag GameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// ���W���擾
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetPosition() const
{
	return m_position;
}

const Vector3& GameObject::GetVelocity() const
{
	return m_velocity;
}

/// <summary>
/// ��]�ʂ��擾
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// �T�C�Y���擾
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetScale() const
{
	return m_scale;
}

DirectX::SimpleMath::Matrix GameObject::GetWorld()
{
	return m_world;
}

DirectX::SimpleMath::Color GameObject::GetColor()
{
	return m_color;
}



/// <summary>
/// �`�揇���擾
/// </summary>
/// <returns></returns>
const int GameObject::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// ���a���擾
/// </summary>
/// <returns></returns>
float GameObject::GetRadius()
{
	return m_radius;
}

/// <summary>
/// �擾���Ă�I�u�W�F�N�g��
/// </summary>
/// <returns></returns>
GameObject::ObjectTag GameObject::GetCharaTag()
{
	return m_charaTag;
}

/// <summary>
/// �^�O����o�^
/// </summary>
/// <param name="tag"></param>
void GameObject::SetTag(const ObjectTag tag)
{
	m_tag = tag;
}

/// <summary>
/// ���W��o�^
/// </summary>
/// <param name="position"></param>
void GameObject::SetPosition(Vector3 position)
{
	m_position = position;
}

void GameObject::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

/// <summary>
/// ��]�ʂ�o�^
/// </summary>
/// <param name="rotation"></param>
void GameObject::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// �T�C�Y��o�^
/// </summary>
/// <param name="scale"></param>
void GameObject::SetScale(Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// �I�u�W�F�N�g�J���[�̓o�^
/// </summary>
/// <param name="color"></param>
void GameObject::SetColor(Color color)
{
	m_color = color;
}

/// <summary>
/// �`�揇��o�^
/// </summary>
/// <param name="prio"></param>
void GameObject::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}

void GameObject::SetCharaTag(ObjectTag tag)
{
	m_charaTag = tag;
}

/// <summary>
/// ��\���ɂ���
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}