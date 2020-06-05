//======================================================
// File Name	 : Bullet.h
// Summary	 : 弾
// Date		: 2020/5/25
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <DirectXTK\SimpleMath.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class Bullet : public GameObject
{
public:
	//コンストラク
	Bullet(const ObjectTag tag, const ObjectTag charaTag,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& azimuth);
	//デストラクタ
	~Bullet();

public:
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render() override;
	//当たった後の処理
	void HitContact(GameObject* object) override;

public:
	//弾のスピード
	static const float MOVE_SPEED;

private:
	//弾のモデル
	std::unique_ptr<DirectX::GeometricPrimitive>  m_sphereModel;
	// コライダー
	std::unique_ptr<SphereCollider> m_collider;

	
};