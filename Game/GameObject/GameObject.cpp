//======================================================
// File Name	: GameObject.h
// Summary	: �Q�[���I�u�W�F�N�g
//======================================================
#include "GameObject.h"

#include <Game\GameObject\ObjectTag.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�^�O��</param>
GameObject::GameObject(const ObjectTag tag)
{
	tag;
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
const ObjectTag GameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// ���W���擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetPosition() const
{
	return m_position;
}

/// <summary>
/// ��]�ʂ��擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// �T�C�Y���擾
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
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
void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}

/// <summary>
/// ��]�ʂ�o�^
/// </summary>
/// <param name="rotation"></param>
void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// �T�C�Y��o�^
/// </summary>
/// <param name="scale"></param>
void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// �`�揇��o�^
/// </summary>
/// <param name="prio"></param>
void GameObject::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}

/// <summary>
/// ��\���ɂ���
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}