//======================================================
// File Name	: IGameObject.h
// Summary	: �Q�[���I�u�W�F�N�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "IGameObject.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�^�O��</param>
IGameObject::IGameObject(const ObjectTag tag)
	: m_tag(tag)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_rotation()
	, m_scale(1.0f, 1.0f, 1.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IGameObject::~IGameObject()
{
}

/// <summary>
/// ����
/// </summary>
void IGameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// �L��
/// </summary>
/// <returns></returns>
bool IGameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// ����
/// </summary>
/// <returns></returns>
bool IGameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// �^�O���擾
/// </summary>
/// <returns></returns>
const IGameObject::ObjectTag IGameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// ���W���擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3& IGameObject::GetPosition() const
{
	return m_position;
}

const DirectX::SimpleMath::Vector3& IGameObject::GetVelocity() const
{
	return m_velocity;
}

/// <summary>
/// ��]�ʂ��擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3& IGameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// �T�C�Y���擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3& IGameObject::GetScale() const
{
	return m_scale;
}

/// <summary>
/// �`�揇���擾
/// </summary>
/// <returns></returns>
const int IGameObject::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// �^�O����o�^
/// </summary>
/// <param name="tag"></param>
void IGameObject::SetTag(const ObjectTag tag)
{
	m_tag = tag;
}

/// <summary>
/// ���W��o�^
/// </summary>
/// <param name="position"></param>
void IGameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}

void IGameObject::SetVelocity(DirectX::SimpleMath::Vector3& velocity)
{
	m_velocity = velocity;
}

/// <summary>
/// ��]�ʂ�o�^
/// </summary>
/// <param name="rotation"></param>
void IGameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// �T�C�Y��o�^
/// </summary>
/// <param name="scale"></param>
void IGameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// �`�揇��o�^
/// </summary>
/// <param name="prio"></param>
void IGameObject::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}

/// <summary>
/// ��\���ɂ���
/// </summary>
/// <param name="object"></param>
void IGameObject::Destroy(IGameObject * object)
{
	object->Invalidate();
}