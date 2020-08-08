//======================================================
// File Name	: BoxCollider.cpp
// Summary		: 箱
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "BoxCollider.h"

#include <Game/Collider/CollisionManager.h>

#include <Game/GameObject/GameObject.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">登録したオブジェクト</param>
/// <param name="size">一辺の半分の長さ</param>
BoxCollider::BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size)
	: Collider(owner)
	, m_size(size)
{
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const BoxCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool BoxCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
