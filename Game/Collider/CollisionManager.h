//======================================================
// File Name	: CollisionManager.h
// Summary		: �R���C�_�[�}�l�W���[
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include <DirectXTK/SimpleMath.h>

#include <Game/Collider/Collider.h>

#include <Game/GameObject/GameObject.h>

class SphereCollider;
class BoxCollider;


class CollisionManager final
{
public:
	struct RaycastHit
	{
		RaycastHit() :distNear(), distFar(), posNear(), posFar(), normNear(), normFar() {
		}

		float distNear;
		float distFar;
		DirectX::SimpleMath::Vector3 posNear;
		DirectX::SimpleMath::Vector3 posFar;
		DirectX::SimpleMath::Vector3 normNear;
		DirectX::SimpleMath::Vector3 normFar;
	};

public:
	using ColliderList       = std::vector<Collider*>;
	using ColliderGroupList  = std::unordered_map<GameObject::ObjectTag, ColliderList>;
	using CollisionGroup     = std::pair<GameObject::ObjectTag, GameObject::ObjectTag>;
	using CollisionGroupList = std::list<CollisionGroup>;

public:
	//�R���X�g���N�^
	CollisionManager();
	//�f�X�g���N�^
	~CollisionManager();

public:
	// �I�u�W�F�N�g��ǉ�
	void Add(GameObject::ObjectTag groupName, Collider* collider);
	// ��������O���[�v���擾
	void AllowCollision(GameObject::ObjectTag groupName1, GameObject::ObjectTag groupName2);
	// �Փ˂����o
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);

public:
	//�����蔻��
	static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
	static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
	static bool IsCollided(const SphereCollider* collider1, const RayCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
	static bool IsCollided(const BoxCollider*    collider1, const RayCollider*    collider2);
	static bool IsCollided(const RayCollider*    collider1, const RayCollider*    collider2);
	static bool IsCollided(const RayCollider*    collider1, const SphereCollider* collider2);
	static bool IsCollided(const RayCollider*    collider1, const BoxCollider*    collider2);


	//�����v�Z
	static float SquareCalculation(const SphereCollider*    collider1, const BoxCollider*    collider2);
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1,
		DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2, float& s, float& t,
		DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	static bool HitCheck_Line2AABB(const BoxCollider* collider1, const RayCollider* collider2, RaycastHit* hit = nullptr);

private:
	//�I�u�W�F�N�g���O���[�v�����ɋL�^
	ColliderGroupList  m_colliderGroups;
	//�Փ˂���O���[�v�����L�^
	CollisionGroupList m_collisionGroups;
};
