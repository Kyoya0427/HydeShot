//======================================================
// File Name	: SphereCollider.h
// Summary		: 球
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	//コンストラクタ
	SphereCollider(GameObject* owner, float radius = 1.0f);
	//デストラクタ
	~SphereCollider() = default;

public:
	//当たったオブジェクトの種類判別
	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider) const override;
	bool IsCollided(const RayCollider*    collider) const override;

public:
	//半径を取得
	float GetRadius() const			  { return m_radius; }
	//半径を設定
	void  SetRadius(float radius)     { m_radius = radius; }

private:
	//半径
	float m_radius;

};
