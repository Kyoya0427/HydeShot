//======================================================
// File Name	: CollisionManager.h
// Summary		: コライダーマネジャー
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include <DirectXTK/SimpleMath.h>

#include <Game/Collider/Collider.h>
#include <Game/Collider/RaycastHit.h>

#include <Game/GameObject/GameObject.h>

class SphereCollider;
class BoxCollider;

class CollisionManager final
{
public:
	using ColliderList       = std::vector<Collider*>;
	using ColliderGroupList  = std::unordered_map<GameObject::ObjectTag, ColliderList>;
	using CollisionGroup     = std::pair<GameObject::ObjectTag, GameObject::ObjectTag>;
	using CollisionGroupList = std::list<CollisionGroup>;

public:
	//コンストラクタ
	CollisionManager();
	//デストラクタ
	~CollisionManager();

public:
	// オブジェクトを追加
	void Add(GameObject::ObjectTag groupName, Collider* collider);
	// 判定を取るグループを取得
	void AllowCollision(GameObject::ObjectTag groupName1, GameObject::ObjectTag groupName2);
	// 衝突を検出
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);

public:
	//当たり判定
	static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
	static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
	static bool IsCollided(const SphereCollider* collider1, const RayCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
	static bool IsCollided(const BoxCollider*    collider1, const RayCollider*    collider2);
	static bool IsCollided(const RayCollider*    collider1, const SphereCollider* collider2);
	static bool IsCollided(const RayCollider*    collider1, const BoxCollider*    collider2);
	static bool IsCollided(const RayCollider* collider1, const RayCollider* collider2);
	//平方計算
	static float SquareCalculation(const SphereCollider*    collider1, const BoxCollider*    collider2);
	//最も近いポイントセグメント
	static float ClosestPointSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
									 DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2, float& s, float& t,
									 DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);
	//線と箱の当たり判定
	static bool LineToAABB(const BoxCollider* collider1, const RayCollider* collider2, RaycastHit* hit = nullptr);

private:
	//オブジェクトをグループ名事に記録
	ColliderGroupList  m_colliderGroups;
	//衝突するグループ名を記録
	CollisionGroupList m_collisionGroups;

};
