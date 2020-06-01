//======================================================
// File Name	: Collider.h
// Summary	: 衝突親クラス
// Date		: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SimpleMath.h>

class GameObject;
class SphereCollider;
class BoxCollider;

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


public:
	//当たった後の処理
	void HitContact(const Collider* object) const;
	// 座標を取得
	const DirectX::SimpleMath::Vector3 GetPosition() const;
	//座標を設定
	 void SetPosition(DirectX::SimpleMath::Vector3 pos);
	 //差引勘定を取得
	const DirectX::SimpleMath::Vector3 GetOffset() const;
	//差引勘定を設定
	void  SetOffset(const DirectX::SimpleMath::Vector3& offset);

protected:
	//オブジェクト
	GameObject*                  m_owner;
	//差引勘定数値
	DirectX::SimpleMath::Vector3 m_offset;
};
