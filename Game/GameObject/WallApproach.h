//======================================================
// File Name	: WallApproach.h
// Summary		: 壁に接近しているか
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK/PrimitiveBatch.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/WallApproachVelID.h>

#include <Game/Collider/BoxCollider.h>

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

public:
	void SetOffsetAngle(float angle);
	//壁に接近しているか
	WallApproachVelID GetWallApproach();
	//壁に接近しているか
	void SetWallApproach(WallApproachVelID approach);

public:
	static const float  FORWARD_ANGLE;
	static const float  BACKWARD_ANGLE;
	static const float  LEFT_ANGLE;
	static const float  RIGHT_ANGLE;

private:
	//当たり判定モデル
	std::unique_ptr<DirectX::GeometricPrimitive> m_WallApproachCollider;
	//当たり判定
	std::unique_ptr<BoxCollider>				 m_collider;
	//サイズ
	DirectX::SimpleMath::Vector3                 m_size;
	//所持してるキャラ
	Character*									 m_chara;

	float                                        m_offsetAngle;

	WallApproachVelID							 m_isWallApproach;
};

