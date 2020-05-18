//======================================================
// File Name	: IGameObject.h
// Summary	: ゲームオブジェクト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "IGameObject.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">タグ名</param>
IGameObject::IGameObject(const ObjectTag tag)
	: m_tag(tag)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_rotation()
	, m_scale(1.0f, 1.0f, 1.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
IGameObject::~IGameObject()
{
}

/// <summary>
/// 無効
/// </summary>
void IGameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// 有効
/// </summary>
/// <returns></returns>
bool IGameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// 無効
/// </summary>
/// <returns></returns>
bool IGameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// タグを取得
/// </summary>
/// <returns></returns>
const IGameObject::ObjectTag IGameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// 座標を取得
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
/// 回転量を取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3& IGameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// サイズを取得
/// </summary>
/// <returns></returns>
const DirectX::SimpleMath::Vector3& IGameObject::GetScale() const
{
	return m_scale;
}

/// <summary>
/// 描画順を取得
/// </summary>
/// <returns></returns>
const int IGameObject::GetDrawPrio() const
{
	return m_drawPrio;
}

/// <summary>
/// タグ名を登録
/// </summary>
/// <param name="tag"></param>
void IGameObject::SetTag(const ObjectTag tag)
{
	m_tag = tag;
}

/// <summary>
/// 座標を登録
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
/// 回転量を登録
/// </summary>
/// <param name="rotation"></param>
void IGameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// サイズを登録
/// </summary>
/// <param name="scale"></param>
void IGameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}

/// <summary>
/// 描画順を登録
/// </summary>
/// <param name="prio"></param>
void IGameObject::SetDrawPrio(int prio)
{
	m_drawPrio = prio;
}

/// <summary>
/// 非表示にする
/// </summary>
/// <param name="object"></param>
void IGameObject::Destroy(IGameObject * object)
{
	object->Invalidate();
}