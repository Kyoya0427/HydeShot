//======================================================
// File Name	: WallApproach.h
// Summary		: 壁に接近しているか
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK/PrimitiveBatch.h>

#include <Game/GameObject/GameObject.h>

#include <Game/Collider/RayCollider.h>

class Character;

class WallApproach : public GameObject
{
public:
	//コンストラクタ
	WallApproach(Character* chara);
	//デストラクタ
	~WallApproach();

public:
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	//当たり判定モデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_WallApproachCollider;
	//当たり判定
	std::unique_ptr<RayCollider>				 m_collider;
	//サイズ
	DirectX::SimpleMath::Vector3                 m_size;
	//所持してるキャラ
	Character*									 m_chara;
	//始点
	DirectX::SimpleMath::Vector3                 m_posA;
	//終点
	DirectX::SimpleMath::Vector3                 m_posB;
	//敵との相対座標
	float						                 m_enemyToDistance;
	//壁との相対座標
	float						                 m_wallToDistance;

};

