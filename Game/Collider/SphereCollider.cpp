//======================================================
// File Name	: SphereCollider.cpp
// Summary	: 球
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "SphereCollider.h"

#include <Game\Collider\CollisionManager.h>

#include <Game\GameObject\GameObject.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">登録したオブジェクト</param>
/// <param name="radius">半径の長さ</param>
SphereCollider::SphereCollider(GameObject* owner, float radius)
	: Collider(owner)
	, m_radius(radius)
{
}

/// <summary>
/// 半径を設定
/// </summary>
/// <param name="radius"></param>
void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}

/// <summary>
/// 半径取得
/// </summary>
/// <returns></returns>
float SphereCollider::GetRadius() const
{
	return m_radius;
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool SphereCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
