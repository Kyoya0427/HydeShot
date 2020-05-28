//======================================================
// File Name	 : ArtilleryShell.h
// Summary	 : 弾
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <DirectXTK\SimpleMath.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class ArtilleryShell : public GameObject
{
public:
	//コンストラク
	ArtilleryShell(const ObjectTag tag, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth);
	//デストラクタ
	~ArtilleryShell();


public:
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render(const DX::StepTimer& timer) override;
	//当たった後の処理
	void HitContact(GameObject* object) override;

public:
	static const float MOVE_SPEED;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	// コライダー
	std::unique_ptr<SphereCollider> m_collider;
};