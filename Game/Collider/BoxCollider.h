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


public:
	//サイズの取得と設定
	void SetSize(const DirectX::SimpleMath::Vector3& size);
	const DirectX::SimpleMath::Vector3& GetSize() const;

private:
	//サイズ
	DirectX::SimpleMath::Vector3 m_size;
};
