//======================================================
// File Name	: Collider.cpp
// Summary		: 衝突親クラス
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "Collider.h"

#include <Game\GameObject\GameObject.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">登録したオブジェクト</param>
Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset(Vector3(0.0f, 0.0f, 0.0f))
{
}

/// <summary>
/// 衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool Collider::IsCollided(const SphereCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");
	collider;
	return false;
}

/// <summary>
/// 衝突した
/// </summary>
/// <param name="collider">オブジェクト</param>
/// <returns></returns>
bool Collider::IsCollided(const BoxCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");
	collider;

	return false;
}

/// <summary>
///  当たった後の処理
/// </summary>
/// <param name="object"></param>
void Collider::OnCollision(const Collider* object) const
{
	m_owner->OnCollision(object->m_owner);
}

/// <summary>
/// 座標を取得
/// </summary>
/// <returns></returns>
const Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}

/// <summary>
/// 座標を設定
/// </summary>
/// <param name="pos"></param>
void Collider::SetPosition(Vector3& pos)
{
	m_owner->SetPosition(pos);
}

/// <summary>
/// 差引勘定を取得
/// </summary>
/// <returns></returns>
const Vector3 Collider::GetOffset() const
{
	return m_offset;
}

/// <summary>
/// 差引勘定を設定
/// </summary>
/// <param name="offset"></param>
void Collider::SetOffset(const Vector3 & offset)
{
	m_offset = offset;
}
