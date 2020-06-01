//======================================================
// File Name	: CollisionManager.cpp
// Summary	: コライダーマネジャー
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"

#include <Game\Common\Utilities.h>

#include <Game\Collider\BoxCollider.h>
#include <Game\Collider\SphereCollider.h>

#include <Game\GameObject\GameObject.h>

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
	: m_colliderGroups()
	, m_collisionGroups()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// 衝突を検出
/// </summary>
void CollisionManager::DetectCollision()
{
	for (const CollisionGroup& collisionGroup : m_collisionGroups)
	{
		if (collisionGroup.second.empty())
		{
			ColliderList& colliders = m_colliderGroups[collisionGroup.first];

			DetectCollision(colliders);
		}
		else
		{
			ColliderList& colliders1 = m_colliderGroups[collisionGroup.first];
			ColliderList& colliders2 = m_colliderGroups[collisionGroup.second];

			DetectCollision(colliders1, colliders2);
		}
	}

	m_colliderGroups.clear();
}

/// <summary>
/// 衝突を検出
/// </summary>
/// <param name="colliders">オブジェクト</param>
void CollisionManager::DetectCollision(const ColliderList& colliders)
{
	int numObjects = colliders.size();

	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (colliders[i]->IsCollided(colliders[j]))
			{
				colliders[i]->HitContact(colliders[j]);
				colliders[j]->HitContact(colliders[i]);
			}
		}
	}
}

/// <summary>
/// 衝突を検出
/// </summary>
/// <param name="colliders1">オブジェクト1</param>
/// <param name="colliders2">オブジェクト2</param>
void CollisionManager::DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2)
{
	for (const Collider* collider1 : colliders1)
	{
		for (const Collider* collider2 : colliders2)
		{
			if (collider1->IsCollided(collider2))
			{
				collider1->HitContact(collider2);
				collider2->HitContact(collider1);
			}
		}
	}
}

/// <summary>
/// オブジェクトを追加
/// </summary>
/// <param name="groupName">グループ名</param>
/// <param name="collider">オブジェクト</param>
void CollisionManager::Add(const std::string& groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}


/// <summary>
/// 判定を取るグループを取得
/// </summary>
/// <param name="groupName1">グループ名</param>
/// <param name="groupName2">グループ名</param>
void CollisionManager::AllowCollision(const std::string& groupName1, const std::string& groupName2)
{
	if (groupName1 == groupName2)
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, ""));
	}
	else
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, groupName2));
	}
}


/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const SphereCollider* collider1, const SphereCollider* collider2)
{
	// 中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d = collider1->GetPosition() - collider2->GetPosition();
	float dist2 = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radiusSum * radiusSum;
}

/// <summary>
/// 箱と箱の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2)
{
	collider1;
	collider2;
	return false;
}

/// <summary>
/// 球と箱の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float sq = SquareCalculation(collider1, collider2);
	return sq < collider1->GetRadius() * collider1->GetRadius();
}

/// <summary>
/// 箱と球の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

/// <summary>
/// 平方計算
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
/// <returns></returns>
float CollisionManager::SquareCalculation(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float point[3] = { collider1->GetPosition().x, collider1->GetPosition().y, collider1->GetPosition().z };
	float min[3] = { collider2->GetPosition().x - collider2->GetSize().x,  collider2->GetPosition().y - collider2->GetSize().y,  collider2->GetPosition().z - collider2->GetSize().z, };
	float max[3] = { collider2->GetPosition().x + collider2->GetSize().x,  collider2->GetPosition().y + collider2->GetSize().y,  collider2->GetPosition().z + collider2->GetSize().z, };

	float sq = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sq += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sq += (v - max[i]) * (v - max[i]);
	}
	return sq;
}


