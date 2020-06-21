//======================================================
// File Name	: CollisionManager.cpp
// Summary		: コライダーマネジャー
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"

#include <Game\Common\Utilities.h>

#include <Game/Collider/BoxCollider.h>
#include <Game/Collider/SphereCollider.h>
#include <Game/Collider/RayCollider.h>

#include <Game\GameObject\GameObject.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
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
		
		if (collisionGroup.second == GameObject::ObjectTag::None)
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
				colliders[i]->OnCollision(colliders[j]);
				colliders[j]->OnCollision(colliders[i]);
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
				collider1->OnCollision(collider2);
				collider2->OnCollision(collider1);
			}
		}
	}
}

/// <summary>
/// オブジェクトを追加
/// </summary>
/// <param name="groupName">グループ名</param>
/// <param name="collider">オブジェクト</param>
void CollisionManager::Add(GameObject::ObjectTag groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}


/// <summary>
/// 判定を取るグループを取得
/// </summary>
/// <param name="groupName1">グループ名</param>
/// <param name="groupName2">グループ名</param>
void CollisionManager::AllowCollision(GameObject::ObjectTag groupName1, GameObject::ObjectTag groupName2)
{
	if (groupName1 == groupName2)
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, GameObject::ObjectTag::None));
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
	return IsCollided(collider2, collider1);
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

bool CollisionManager::IsCollided(const SphereCollider* collider1, const RayCollider* collider2)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// カプセルの中心の線分間の距離の平方を計算
	DirectX::SimpleMath::Vector3 sphereTop = collider1->GetPosition();
	DirectX::SimpleMath::Vector3 sphereBot = collider1->GetPosition();
	sphereTop.y += collider1->GetRadius();
	sphereBot.y -= collider1->GetRadius();
	float dist2 = ClosestPtSegmentSegment(collider2->GetPosA(), collider2->GetPosB(), sphereTop, sphereBot, s, t, c1, c2);
	float radius = collider1->GetRadius();
	return dist2 < radius;
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

bool CollisionManager::IsCollided(const RayCollider* collider1, const SphereCollider* collider2)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// カプセルの中心の線分間の距離の平方を計算
	DirectX::SimpleMath::Vector3 sphereTop = collider2->GetPosition();
	DirectX::SimpleMath::Vector3 sphereBot = collider2->GetPosition();
	sphereTop.y += collider2->GetRadius();
	sphereBot.y -= collider2->GetRadius();
	float dist2 = ClosestPtSegmentSegment(collider1->GetPosA(), collider1->GetPosB(), sphereTop, sphereBot, s, t, c1, c2);
	float radius = collider2->GetRadius();
	return dist2 < radius;
}

bool CollisionManager::IsCollided(const RayCollider* collider1, const BoxCollider* collider2)
{
	collider1;
	collider2;
	
	return false;
}

bool CollisionManager::IsCollided(const BoxCollider* collider1, const RayCollider* collider2)
{
	RaycastHit hit;
	bool b = HitCheck_Line2AABB(collider1, collider2, &hit);
	float dist = Vector3::Distance(collider2->GetPosA(), collider2->GetPosB());
	return b && 0 < hit.distFar && 0 < (dist - hit.distNear);
}

bool CollisionManager::IsCollided(const RayCollider* collider1, const RayCollider* collider2)
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

float CollisionManager::ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1, DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2, float& s, float& t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
{
	DirectX::SimpleMath::Vector3 d1 = q1 - p1;
	DirectX::SimpleMath::Vector3 d2 = q2 - p2;
	DirectX::SimpleMath::Vector3 r = p1 - p2;
	float a = d1.Dot(d1); float e = d2.Dot(d2); float f = d2.Dot(r);
	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return (c1 - c2).Dot(c1 - c2);
	}
	if (a <= FLT_EPSILON)
	{
		s = 0.0f;
		t = f / e;
		t = Clamp(t, 0.0f, 1.0f);
	}
	else
	{
		float c = d1.Dot(r);
		if (e <= FLT_EPSILON)
		{
			t = 0.0f;
			s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			float b = d1.Dot(d2);
			float denom = a * e - b * b;
			if (denom != 0.0f)
			{
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				s = 0.0f;
			}
			float tnom = (b * s + f);
			if (tnom < 0.0f)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (tnom > e)
			{
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
			else
			{
				t = tnom / e;
			}
		}
	}
	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;
	return (c1 - c2).Dot(c1 - c2);
}

bool CollisionManager::HitCheck_Line2AABB(const BoxCollider* collider1, const RayCollider* collider2, RaycastHit* hit)
{
	Vector3 p_l = collider2->GetPosA();
	Vector3 dir_l = collider2->GetPosB() - collider2->GetPosA();

	// 方向ベクトル正規化
	dir_l.Normalize();

	// 交差判定
	union
	{
		float f[3];
		XMFLOAT3 v;
	} p, d, min, max, tmp_t_norm, t_max_norm;

	p.v = p_l;
	d.v = dir_l;
	min.v = collider1->GetPosition() - collider1->GetSize();
	max.v = collider1->GetPosition() + collider1->GetSize();

	float tmp_t = -FLT_MAX;
	float t_max = FLT_MAX;
	for (int i = 0; i < 3; ++i)
	{
		if (abs(d.f[i]) < FLT_EPSILON)
		{
			if (p.f[i] < min.f[i] || p.f[i] > max.f[i])
				return false; // 交差していない
		}
		else
		{
			// スラブとの距離を算出
			// t1が近スラブ、t2が遠スラブとの距離
			float odd = 1.0f / d.f[i];
			float t1 = (min.f[i] - p.f[i]) * odd;
			float t2 = (max.f[i] - p.f[i]) * odd;
			if (t1 > t2)
				std::swap(t1, t2);
			if (t1 > tmp_t) { tmp_t = t1; tmp_t_norm.v = Vector3::Zero; tmp_t_norm.f[i] = d.f[i] > 0 ? -1.0f : 1.0f; }
			if (t2 < t_max) { t_max = t2; t_max_norm.v = Vector3::Zero; t_max_norm.f[i] = d.f[i] < 0 ? -1.0f : 1.0f; }
			// スラブ交差チェック
			if (tmp_t >= t_max)
				return false;
		}
	}

	if (hit)
	{
		hit->distNear = tmp_t;
		hit->distFar = t_max;
		hit->posNear = p_l + tmp_t * dir_l;
		hit->posFar = p_l + t_max * dir_l;
		hit->normNear = tmp_t_norm.v;
		hit->normFar = t_max_norm.v;
	}
	// 交差している
	return true;
}


