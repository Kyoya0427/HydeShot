//======================================================
// File Name	: Character.h
// Summary		: プレイヤークラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/GeometricPrimitive.h>

#include <Game/GameObject/GameObject.h>


#include <Game/Common/StepTimer.h>

#include <Game/Collider/SphereCollider.h>

class Sight;

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
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

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
	void Shoot();

public:
	int GetHp();
	bool GetWallContact();
	void SetWallContact(bool contact);
	bool GetEnemyContact();
	void SetEnemyContact(bool contact);
public:
	static const int  MAX_HP;

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	std::unique_ptr<Sight>                       m_sight;

	DirectX::SimpleMath::Vector3                 m_previousPos;

	//当たり判定
	std::unique_ptr<SphereCollider>              m_collider;
	
	bool                                         m_wallContact;
	bool                                         m_enemyContact;
	//HP
	int                                          m_hp;
};