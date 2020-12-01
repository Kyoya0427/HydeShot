//======================================================
// File Name	: GameObject.cpp
// Summary		: �Q�[���I�u�W�F�N�g
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�^�O��</param>
GameObject::GameObject(const ObjectTag& tag)
	: m_tag(tag)
	, m_isValid(true)
	, m_drawPrio()
	, m_position()
	, m_velocity()
	, m_rotation()
	, m_scale(1.0f,1.0f,1.0f)
	, m_world()
	, m_color()
	, m_x() , m_y()
	, m_radius()
	, m_charaTag()
	
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
bool GameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// ����
/// </summary>
bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// ��\���ɂ���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}

