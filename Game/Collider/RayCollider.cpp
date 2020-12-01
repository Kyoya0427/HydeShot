//======================================================
// File Name	: RayCollider.cpp
// Summary		: レイ
// Author		: Kyoya Sakamoto
//======================================================
#include "RayCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">登録したオブジェクト</param>
/// <param name="size">一辺の半分の長さ</param>
RayCollider::RayCollider(GameObject* owner)
	: Collider(owner)
	, m_posA()
	, m_posB()
{
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool RayCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool RayCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool RayCollider::IsCollided(const BoxCollider* collider) const
{
	return  CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool RayCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
