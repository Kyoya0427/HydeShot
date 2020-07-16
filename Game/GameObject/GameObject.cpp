//======================================================
// File Name	: GameObject.cpp
// Summary		: ゲームオブジェクト
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">タグ名</param>
GameObject::GameObject(const ObjectTag tag)
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
/// <returns></returns>
bool GameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// 無効
/// </summary>
/// <returns></returns>
bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// タグを取得
/// </summary>
/// <returns></returns>
const GameObject::ObjectTag GameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// 座標を取得
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetPosition() const
{
	return m_position;
}

/// <summary>
/// ベロシティーを取得
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetVelocity() const
{
	return m_velocity;
}

/// <summary>
/// 回転量を取得
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// サイズを取得
/// </summary>
/// <returns></returns>
const Vector3& GameObject::GetScale() const
{
	return m_scale;
}

/// <summary>
/// ワールド座標を取得
/// </summary>
/// <returns></returns>
Matrix GameObject::GetWorld()
{
	return m_world;
}

/// <summary>
/// カラーを取得
/// </summary>
/// <returns></returns>
Color GameObject::GetColor()
{
	return m_color;
}



/// <summary>
/// 描画順を取得
/// </summary>
/// <returns></returns>
const int GameObject::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// 半径を取得
/// </summary>
/// <returns></returns>
float GameObject::GetRadius()
{
	return m_radius;
}

/// <summary>
/// デグリでY軸を返す(0～360)
/// </summary>
/// <returns></returns>
float GameObject::GetRadiansY()
{
	float radians = XMConvertToRadians(XMConvertToDegrees(m_rotation.y)); 
	if (radians > XM_PI *2)
		m_rotation.y = 0.0f;
	if (radians < -XM_PI * 2)
		m_rotation.y = 0.0f;

	if (m_rotation.y < 0.0f)
		radians = XM_PI * 2 + radians;
	return radians;
}

/// <summary>
/// 取得してるオブジェクト名
/// </summary>
/// <returns></returns>
GameObject::ObjectTag GameObject::GetCharaTag()
{
	return m_charaTag;
}

/// <summary>
/// タグ名を登録
/// </summary>
/// <param name="tag"></param>
void GameObject::SetTag(const ObjectTag tag)
{
	m_tag = tag;
}

/// <summary>
/// 座標を登録
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
/// 回転量を登録
/// </summary>
/// <param name="rotation"></param>
void GameObject::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// サイズを登録
/// </summary>
/// <param name="scale"></param>
void GameObject::SetScale(Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// オブジェクトカラーの登録
/// </summary>
/// <param name="color"></param>
void GameObject::SetColor(Color color)
{
	m_color = color;
}

/// <summary>
/// 描画順を登録
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
/// 非表示にする
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}