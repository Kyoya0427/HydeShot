//======================================================
// File Name	: GameObject.cpp
// Summary		: ゲームオブジェクト
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">タグ名</param>
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
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// 無効
/// </summary>
void GameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// 有効
/// </summary>
bool GameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// 無効
/// </summary>
bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// 非表示にする
/// </summary>
/// <param name="object">オブジェクト</param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}

