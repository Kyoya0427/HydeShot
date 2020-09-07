//======================================================
// File Name	: BoxCollider.h
// Summary		: 箱
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
public:
	//コンストラクタ
	BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	//デストラクタ
	~BoxCollider() = default;

public:
	//当たったオブジェクトの種類判別
	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;
	bool IsCollided(const BoxCollider*    collider) const override;
	bool IsCollided(const RayCollider*    collider) const override;

public:
	//サイズの取得と設定
	const DirectX::SimpleMath::Vector3& GetSize() const		   { return m_size; }
	void SetSize(const DirectX::SimpleMath::Vector3& size)     { m_size = size; }

private:
	//サイズ
	DirectX::SimpleMath::Vector3 m_size;

};
