//======================================================
// File Name	: SphereCollider.cpp
// Summary		: 球
// Author		: Kyoya Sakamoto
//======================================================
#include "SphereCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

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
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool SphereCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool SphereCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool SphereCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool SphereCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}