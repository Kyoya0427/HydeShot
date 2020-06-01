//======================================================
// File Name	: CollisionManager.h
// Summary	: コライダーマネジャー
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <vector>
#include <memory>
#include <DirectXTK\SimpleMath.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Collider.h"

class GameObject;
class SphereCollider;
class BoxCollider;


class CollisionManager final
{
	using ColliderList       = std::vector<Collider*>;
	using ColliderGroupList  = std::unordered_map<std::string, ColliderList>;
	using CollisionGroup     = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;

public:
	//コンストラクタ
	CollisionManager();
	//デストラクタ
	~CollisionManager();

public:
	// オブジェクトを追加
	void Add(const std::string& groupName, Collider* collider);
	// 判定を取るグループを取得
	void AllowCollision(const std::string& groupName1, const std::string& groupName2);
	// 衝突を検出
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);


public:
	//当たり判定
	static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
	static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
	static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
	//平方計算
	static float SquareCalculation(const SphereCollider*    collider1, const BoxCollider*    collider2);

private:
	//オブジェクトをグループ名事に記録
	ColliderGroupList  m_colliderGroups;
	//衝突するグループ名を記録
	CollisionGroupList m_collisionGroups;
};
