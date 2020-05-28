
#include "CollisionManager.h"


#include <Game\Collider\BoxCollider.h>
#include <Game\Collider\SphereCollider.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Common\Utilities.h>


CollisionManager::CollisionManager()
	: m_colliderGroups()
	, m_collisionGroups()
{
}



CollisionManager::~CollisionManager()
{
}



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



void CollisionManager::Add(const std::string& groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}



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



bool CollisionManager::IsCollided(const SphereCollider* collider1, const SphereCollider* collider2)
{
	// ’†SŠÔ‚Ì‹——£‚Ì•½•û‚ðŒvŽZ
	DirectX::SimpleMath::Vector3 d = collider1->GetPosition() - collider2->GetPosition();
	float dist2 = d.Dot(d);
	// •½•û‚µ‚½‹——£‚ª•½•û‚µ‚½”¼Œa‚Ì‡Œv‚æ‚è‚à¬‚³‚¢ê‡‚É‹…‚ÍŒð·‚µ‚Ä‚¢‚é
	float radiusSum = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radiusSum * radiusSum;
}



bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2)
{
	collider1;
	collider2;
	return false;
}



bool CollisionManager::IsCollided(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float sq = SquareCalculation(collider1, collider2);
	return sq < collider1->GetRadius() * collider1->GetRadius();
}



bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2)
{
	return IsCollided(collider2, collider1);
}

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


