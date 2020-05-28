//======================================================
// File Name	: Character.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\GeometricPrimitive.h>

#include <Game\GameObject\GameObject.h>

#include <Game\Common\StepTimer.h>

#include <Game\Collider\SphereCollider.h>

class Character : public GameObject
{
public:
	//コンストラク
	Character(const ObjectTag tag = ObjectTag::None);
	//デストラクタ
	~Character();

public:
	// 初期化関数
	void Initialize(DirectX::SimpleMath::Vector2& pos);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render(const DX::StepTimer& timer) override;
	//当たった後の処理
	void HitContact(GameObject* object) override;

public:
	//前進
	void Forward  (float speed);
	//後進
	void Backward (float speed);
	//左に進む
	void Leftward (float speed);
	//右に進む
	void Rightward(float speed);
	//左に旋回
	void LeftTurn (float speed);
	//右に旋回
	void RightTurn(float speed);
	//発砲
	void Shooting();

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	DirectX::SimpleMath::Vector3                 m_previousPos;

	//当たり判定
	std::unique_ptr<SphereCollider>  m_collider;
};