//======================================================
// File Name	: Collider.h
// Summary		: コライダー親クラス
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK/SimpleMath.h>

#include <Game/GameObject/GameObject.h>

class GameObject;
class SphereCollider;
class BoxCollider;
class RayCollider;

class Collider
{
public:
	//コンストラクタ
	Collider(GameObject* owner);
	//デストラクタ
	virtual ~Collider() = default;

public:
	//当たったオブジェクトの種類判別
	virtual bool IsCollided(const Collider*       collider) const = 0;
	virtual bool IsCollided(const SphereCollider* collider) const;
	virtual bool IsCollided(const BoxCollider*    collider) const;
	virtual bool IsCollided(const RayCollider*    collider) const;

public:
	//当たった後の処理
	void OnCollision(const Collider* object) const;

public:
	 //差引勘定を取得
	const DirectX::SimpleMath::Vector3& GetOffset() const   { return m_offset;}
	//オブジェクトを取得
	GameObject* GetGameObject()								{ return m_owner; }
	// 座標を取得
	DirectX::SimpleMath::Vector3 GetPosition() const;

public:
	//座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos)  { m_owner->SetPosition(pos); }
	//差引勘定を設定
	void SetOffset(const DirectX::SimpleMath::Vector3& offset) { m_offset = offset; }

private:
	//オブジェクト
	GameObject*                         m_owner;
	//差引勘定数値
	DirectX::SimpleMath::Vector3		m_offset;

};

/// <summary>
/// 座標を取得
/// </summary>
/// <returns>座標</returns>
inline DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}