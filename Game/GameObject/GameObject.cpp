//======================================================
// File Name	: GameObject.h
// Summary	: ゲームオブジェクト
//======================================================
#include "GameObject.h"

#include <Game\GameObject\ObjectTag.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">タグ名</param>
GameObject::GameObject(const ObjectTag tag)
{
	tag;
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
const ObjectTag GameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// 座標を取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetPosition() const
{
	return m_position;
}

/// <summary>
/// 回転量を取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// サイズを取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
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
void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}

/// <summary>
/// 回転量を登録
/// </summary>
/// <param name="rotation"></param>
void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// サイズを登録
/// </summary>
/// <param name="scale"></param>
void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// 描画順を登録
/// </summary>
/// <param name="prio"></param>
void GameObject::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}

/// <summary>
/// 非表示にする
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}