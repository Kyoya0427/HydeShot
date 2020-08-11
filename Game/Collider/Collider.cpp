//======================================================
// File Name	: Collider.cpp
// Summary		: コライダー親クラス
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "Collider.h"

#include <Game/GameObject/GameObject.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">登録したオブジェクト</param>
Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset()
{
}

/// <summary>
/// 衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool Collider::IsCollided(const SphereCollider* collider) const
{
	collider;
	return false;
}

/// <summary>
/// 衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool Collider::IsCollided(const BoxCollider* collider) const
{
	collider;

	return false;
}

/// <summary>
/// 衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
bool Collider::IsCollided(const RayCollider* collider) const
{
	collider;

	return false;
}

/// <summary>
/// 当たった後の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Collider::OnCollision(const Collider* object) const
{
	m_owner->OnCollision(object->m_owner);
}
