//======================================================
// File Name	: CollisionManager.h
// Summary	: �R���C�_�[�}�l�W���[
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
	//�R���X�g���N�^
	CollisionManager();
	//�f�X�g���N�^
	~CollisionManager();

public:
	// �I�u�W�F�N�g��ǉ�
	void Add(const std::string& groupName, Collider* collider);
	// ��������O���[�v���擾
	void AllowCollision(const std::string& groupName1, const std::string& groupName2);
	// �Փ˂����o
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);


public:
	//�����蔻��
	static bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2);
	static bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2);
	static bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2);
	static bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2);
	//�����v�Z
	static float SquareCalculation(const SphereCollider*    collider1, const BoxCollider*    collider2);

private:
	//�I�u�W�F�N�g���O���[�v�����ɋL�^
	ColliderGroupList  m_colliderGroups;
	//�Փ˂���O���[�v�����L�^
	CollisionGroupList m_collisionGroups;
};
