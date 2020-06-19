//======================================================
// File Name	: RayCollider.cpp
// Summary		: レイ
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "RayCollider.h"

#include <Game\Collider\CollisionManager.h>

#include <Game\GameObject\GameObject.h>

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
/// <returns></returns>
bool RayCollider::IsCollided(const Collider* collider) const
{
	return collider->IsCollided(this);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool RayCollider::IsCollided(const SphereCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

bool RayCollider::IsCollided(const BoxCollider* collider) const
{
	return  CollisionManager::IsCollided(this, collider);
}

/// <summary>
///  衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool RayCollider::IsCollided(const RayCollider* collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

/// <summary>
/// A座標を取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 RayCollider::GetPosA() const
{
	return m_posA;
}

/// <summary>
/// B座標を取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 RayCollider::GetPosB() const
{
	return m_posB;
}

/// <summary>
/// A座標を設定
/// </summary>
/// <param name="posA"></param>
void RayCollider::SetPosA(DirectX::SimpleMath::Vector3 posA)
{
	m_posA = posA;
}

/// <summary>
/// B座標に設定
/// </summary>
/// <param name="posB"></param>
void RayCollider::SetPosB(DirectX::SimpleMath::Vector3 posB)
{
	m_posB = posB;
}


