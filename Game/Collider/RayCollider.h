//======================================================
// File Name	: RayCollider.h
// Summary		: 箱
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class RayCollider : public Collider
{
public:
	//コンストラクタ
	RayCollider(GameObject* owner);
	//デストラクタ
	~RayCollider() = default;

public:
	//当たったオブジェクトの種類判別
	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider)	const override;
	bool IsCollided(const RayCollider*    collider) const override;

public:
	//始点と終点を取得
	const DirectX::SimpleMath::Vector3& GetPosA() const    { return m_posA; }
	const DirectX::SimpleMath::Vector3& GetPosB() const    { return m_posB; }
	void SetPosA(const DirectX::SimpleMath::Vector3& posA) { m_posA = posA; }
	void SetPosB(const DirectX::SimpleMath::Vector3& posB) { m_posB = posB; }

private:
	//始点
	DirectX::SimpleMath::Vector3		m_posA;
	//終点
	DirectX::SimpleMath::Vector3		m_posB;

};
