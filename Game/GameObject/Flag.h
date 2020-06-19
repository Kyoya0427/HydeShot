//======================================================
// File Name	: Flag.h
// Summary		: 旗
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK\GeometricPrimitive.h>
#include <Game\GameObject\GameObject.h>

#include <Game\Collider\SphereCollider.h>

class Flag : public GameObject
{
public:
	//コンストラクタ
	Flag(const ObjectTag tag = ObjectTag::None);
	//デストラクタ
	~Flag();
public:
	// 初期化関数
	void Initialize(int x, int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	//当たり判定
	std::unique_ptr<SphereCollider>				 m_collider;

};