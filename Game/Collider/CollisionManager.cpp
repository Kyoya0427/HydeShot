//======================================================
// File Name	: CollisionManager.cpp
// Summary	: �R���C�_�[�}�l�W���[
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"

#include <Game\Common\Utilities.h>

#include <Game\Collider\BoxCollider.h>
#include <Game\Collider\SphereCollider.h>

#include <Game\GameObject\GameObject.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
	: m_colliderGroups()
	, m_collisionGroups()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// �Փ˂����o
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
/// �Փ˂����o
/// </summary>
/// <param name="colliders">�I�u�W�F�N�g</param>
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
/// �Փ˂����o
/// </summary>
/// <param name="colliders1">�I�u�W�F�N�g1</param>
/// <param name="colliders2">�I�u�W�F�N�g2</param>
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
/// �I�u�W�F�N�g��ǉ�
/// </summary>
/// <param name="groupName">�O���[�v��</param>
/// <param name="collider">�I�u�W�F�N�g</param>
void CollisionManager::Add(const std::string& groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}


/// <summary>
/// ��������O���[�v���擾
/// </summary>
/// <param name="groupName1">�O���[�v��</param>
/// <param name="groupName2">�O���[�v��</param>
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
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g�P</param>
/// <param name="collider2">�I�u�W�F�N�g�Q</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const SphereCollider* collider1, const SphereCollider* collider2)
{
	// ���S�Ԃ̋����̕������v�Z
	DirectX::SimpleMath::Vector3 d = collider1->GetPosition() - collider2->GetPosition();
	float dist2 = d.Dot(d);
	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
	float radiusSum = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radiusSum * radiusSum;
}

/// <summary>
/// ���Ɣ��̓����蔻��
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g�P</param>
/// <param name="collider2">�I�u�W�F�N�g�Q</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2)
{
	collider1;
	collider2;
	return false;
}

/// <summary>
/// ���Ɣ��̓����蔻��
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g�P</param>
/// <param name="collider2">�I�u�W�F�N�g�Q</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float sq = SquareCalculation(collider1, collider2);
	return sq < collider1->GetRadius() * collider1->GetRadius();
}

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g�P</param>
/// <param name="collider2">�I�u�W�F�N�g�Q</param>
/// <returns></returns>
bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

/// <summary>
/// �����v�Z
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g�P</param>
/// <param name="collider2">�I�u�W�F�N�g�Q</param>
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


