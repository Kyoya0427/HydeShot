//======================================================
// File Name	: CollisionManager.cpp
// Summary		: コライダーマネジャー
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"

#include <Game/Common/Utilities.h>

#include <Game/Collider/BoxCollider.h>
#include <Game/Collider/SphereCollider.h>
#include <Game/Collider/RayCollider.h>

#include <Game/GameObject/GameObject.h>

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
bool CollisionManager::IsCollided(const SphereCollider* collider1, const SphereCollider* collider2)
{
	//中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d       = collider1->GetPosition() - collider2->GetPosition();
	float dist2     = d.Dot(d);
	//平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = collider1->GetRadius() + collider2->GetRadius();
	return dist2   <= radiusSum * radiusSum;
}

/// <summary>
/// 箱とレイの当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const RayCollider* collider2)
{
	RaycastHit hit;
	bool b     = LineToAABB(collider1, collider2, &hit);
	float dist = DirectX::SimpleMath::Vector3::Distance(collider2->GetPosA(), collider2->GetPosB());
	
	return b && 0 < hit.distFar && 0 < (dist - hit.distNear);
}

/// <summary>
/// 箱とレイの当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
bool CollisionManager::IsCollided(const RayCollider* collider1, const BoxCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

/// <summary>
/// 球と箱の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
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
bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

/// <summary>
/// 球とレイの当たり判定
/// </summary>
/// <param name="collider1">オブジェクト1</param>
/// <param name="collider2">オブジェクト2</param>
bool CollisionManager::IsCollided(const SphereCollider* collider1, const RayCollider* collider2)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	//カプセルの中心の線分間の距離の平方を計算
	DirectX::SimpleMath::Vector3 sphereTop = collider1->GetPosition();
	DirectX::SimpleMath::Vector3 sphereBot = collider1->GetPosition();
	sphereTop.y      += collider1->GetRadius();
	sphereBot.y      -= collider1->GetRadius();
	float dist2       = ClosestPointSegment(collider2->GetPosA(), collider2->GetPosB(), sphereTop, sphereBot, s, t, c1, c2);
	float radius      = collider1->GetRadius();
	return dist2 < radius;
}

/// <summary>
/// 球とレイの当たり判定
/// </summary>
/// <param name="collider1">オブジェクト1</param>
/// <param name="collider2">オブジェクト2</param>
bool CollisionManager::IsCollided(const RayCollider* collider1, const SphereCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

/// <summary>
/// 箱と箱の当たり判定
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2)
{
	if (fabsf(collider1->GetPosition().x - collider2->GetPosition().x) > (collider1->GetSize().x + collider1->GetSize().x)) return false;
	if (fabsf(collider1->GetPosition().y - collider2->GetPosition().y) > (collider1->GetSize().y + collider1->GetSize().y)) return false;
	if (fabsf(collider1->GetPosition().z - collider2->GetPosition().z) > (collider1->GetSize().z + collider1->GetSize().z)) return false;
	return true;
}

/// /// <summary>
/// 平方計算
/// </summary>
/// <param name="collider1">オブジェクト１</param>
/// <param name="collider2">オブジェクト２</param>
float CollisionManager::SquareCalculation(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float point[3] = { collider1->GetPosition().x, collider1->GetPosition().y, collider1->GetPosition().z };
	float min[3]   = { collider2->GetPosition().x - collider2->GetSize().x,  collider2->GetPosition().y - collider2->GetSize().y,  collider2->GetPosition().z - collider2->GetSize().z, };
	float max[3]   = { collider2->GetPosition().x + collider2->GetSize().x,  collider2->GetPosition().y + collider2->GetSize().y,  collider2->GetPosition().z + collider2->GetSize().z, };

	float sq = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sq += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sq += (v - max[i]) * (v - max[i]);
	}
	return sq;
}

/// <summary>
/// ２つの線分の最短距離の平方を返す関数
/// </summary>
/// <param name="p1">線分１の始点</param>
/// <param name="q1">線分１の終点</param>
/// <param name="p2">線分２の始点</param>
/// <param name="q2">線分２の終点</param>
/// <param name="s">線分１上の最短位置を表す係数</param>
/// <param name="t">線分２上の最短位置を表す係数</param>
/// <param name="c1">線分１上の最短距離の位置</param>
/// <param name="c2">線分２上の最短距離の位置</param>
/// <returns>２つの線分の最短距離の平方</returns>
float CollisionManager::ClosestPointSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1, 
	                                        DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2, 
	                                        float& s, float& t, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
{
	DirectX::SimpleMath::Vector3 d1 = q1 - p1;
	DirectX::SimpleMath::Vector3 d2 = q2 - p2;
	DirectX::SimpleMath::Vector3 r = p1 - p2;

	float a = d1.Dot(d1); float e = d2.Dot(d2); float f = d2.Dot(r);
	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		s  = t = 0.0f;
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

/// <summary>
/// 線と箱の当たり判定
/// </summary>
/// <param name="collider1">ボックスオブジェクト</param>
/// <param name="collider2">線オブジェクト</param>
/// <param name="hit">法線</param>
/// <returns>交差判定</returns>
bool CollisionManager::LineToAABB(const BoxCollider* collider1, const RayCollider* collider2, RaycastHit* hit)
{
	DirectX::SimpleMath::Vector3 p_l   = collider2->GetPosA();
	DirectX::SimpleMath::Vector3 dir_l = collider2->GetPosB() - collider2->GetPosA();

	//方向ベクトル正規化
	dir_l.Normalize();

	//交差判定
	union
	{
		float f[3];
		DirectX::XMFLOAT3 v;
	} p, d, min, max, tmp_t_norm, t_max_norm;

	p.v   = p_l;
	d.v   = dir_l;
	min.v = collider1->GetPosition() - collider1->GetSize();
	max.v = collider1->GetPosition() + collider1->GetSize();

	float tmp_t = -FLT_MAX;
	float t_max = FLT_MAX;
	for (int i = 0; i < 3; ++i)
	{
		if (abs(d.f[i]) < FLT_EPSILON)
		{
			if (p.f[i] < min.f[i] || p.f[i] > max.f[i])
				return false; //交差していない
		}
		else
		{
			//スラブとの距離を算出
			//t1が近スラブ、t2が遠スラブとの距離
			float odd = 1.0f / d.f[i];
			float t1  = (min.f[i] - p.f[i]) * odd;
			float t2  = (max.f[i] - p.f[i]) * odd;
			if (t1 > t2)
				std::swap(t1, t2);
			if (t1 > tmp_t) { tmp_t = t1; tmp_t_norm.v = DirectX::SimpleMath::Vector3::Zero; tmp_t_norm.f[i] = d.f[i] > 0 ? -1.0f : 1.0f; }
			if (t2 < t_max) { t_max = t2; t_max_norm.v = DirectX::SimpleMath::Vector3::Zero; t_max_norm.f[i] = d.f[i] < 0 ? -1.0f : 1.0f; }
			// スラブ交差チェック
			if (tmp_t >= t_max)
				return false;
		}
	}

	if (hit)
	{
		hit->distNear = tmp_t;
		hit->distFar  = t_max;
		hit->posNear  = p_l + tmp_t * dir_l;
		hit->posFar   = p_l + t_max * dir_l;
		hit->normNear = tmp_t_norm.v;
		hit->normFar  = t_max_norm.v;
	}
	//交差している
	return true;
}

bool CollisionManager::IsCollided(const RayCollider* collider1, const RayCollider* collider2)
{
	collider1;
	collider2;
	return false;
}