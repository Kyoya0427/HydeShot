//======================================================
// File Name	: CollisionManager.cpp
// Summary		: �R���C�_�[�}�l�W���[
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"

#include <Game\Common\Utilities.h>

#include <Game/Collider/BoxCollider.h>
#include <Game/Collider/SphereCollider.h>
#include <Game/Collider/RayCollider.h>

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
				colliders[i]->OnCollision(colliders[j]);
				colliders[j]->OnCollision(colliders[i]);
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
				collider1->OnCollision(collider2);
				collider2->OnCollision(collider1);
			}
		}
	}
}

/// <summary>
/// �I�u�W�F�N�g��ǉ�
/// </summary>
/// <param name="groupName">�O���[�v��</param>
/// <param name="collider">�I�u�W�F�N�g</param>
void CollisionManager::Add(GameObject::ObjectTag groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}


/// <summary>
/// ��������O���[�v���擾
/// </summary>
/// <param name="groupName1">�O���[�v��</param>
/// <param name="groupName2">�O���[�v��</param>
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

bool CollisionManager::IsCollided(const SphereCollider* collider1, const RayCollider* collider2)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// �J�v�Z���̒��S�̐����Ԃ̋����̕������v�Z
	DirectX::SimpleMath::Vector3 sphereTop = collider1->GetPosition();
	DirectX::SimpleMath::Vector3 sphereBot = collider1->GetPosition();
	sphereTop.y += collider1->GetRadius();
	sphereBot.y -= collider1->GetRadius();
	float dist2 = ClosestPtSegmentSegment(collider2->GetPosA(), collider2->GetPosB(), sphereTop, sphereBot, s, t, c1, c2);
	float radius = collider1->GetRadius();
	return dist2 < radius;
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

bool CollisionManager::IsCollided(const RayCollider* collider1, const SphereCollider* collider2)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// �J�v�Z���̒��S�̐����Ԃ̋����̕������v�Z
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
	DirectX::SimpleMath::Vector3 posA = collider2->GetPosA();
	DirectX::SimpleMath::Vector3 posB = collider2->GetPosB();
	posB.Normalize();
	// ���������E�{�b�N�X�̋�Ԃֈړ�
	DirectX::SimpleMath::Matrix invMat = collider2->GetGameObject()->GetWorld().Invert();
	DirectX::SimpleMath::Vector3 p_l, dir_l;
	p_l = DirectX::SimpleMath::Vector3::Transform(posA, invMat);
	invMat._41 = 0.0f;
	invMat._42 = 0.0f;
	invMat._43 = 0.0f;
	dir_l = DirectX::SimpleMath::Vector3::Transform(posB, invMat);
	// ��������
	float p[3], d[3], min[3], max[3];
	memcpy(p, &p_l, sizeof(DirectX::SimpleMath::Vector3));
	memcpy(d, &dir_l, sizeof(DirectX::SimpleMath::Vector3));
	min[0] = collider1->GetPosition().x - collider1->GetSize().x ;
	min[1] = collider1->GetPosition().y - collider1->GetSize().y ;
	min[2] = collider1->GetPosition().z - collider1->GetSize().z ;
	max[0] = collider1->GetPosition().x + collider1->GetSize().x ;
	max[1] = collider1->GetPosition().y + collider1->GetSize().y ;
	max[2] = collider1->GetPosition().z + collider1->GetSize().z ;
	float tmp_t = -FLT_MAX;
	float t_max = FLT_MAX;
	for (int i = 0; i < 3; ++i) {
		if (abs(d[i]) < FLT_EPSILON) {
			if (p[i] < min[i] || p[i] > max[i])
				return false; // �������Ă��Ȃ�
		}
		else {
			// �X���u�Ƃ̋������Z�o
			// t1���߃X���u�At2�����X���u�Ƃ̋���
			float odd = 1.0f / d[i];
			float t1 = (min[i] - p[i]) * odd;
			float t2 = (max[i] - p[i]) * odd;
			if (t1 > t2) {
				float tmp = t1; t1 = t2; t2 = tmp;
			}
			if (t1 > tmp_t) tmp_t = t1;
			if (t2 < t_max) t_max = t2;
			// �X���u�����`�F�b�N
			if (tmp_t >= t_max)
				return false;
		}
	}

	return true;
}

bool CollisionManager::IsCollided(const RayCollider* collider1, const RayCollider* collider2)
{
	return false;
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


