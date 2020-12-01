//======================================================
// File Name	: WallApproach.h
// Summary		: 壁に接近しているか
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
	//壁に接近しているか
	const WallApproachVelID& GetWallApproach() const        { return m_isWallApproach; }

public:
	//壁に接近しているか設定
	void SetWallApproach(const WallApproachVelID& approach) { m_isWallApproach = approach; }
	//オフセットを設定
	void SetOffsetAngle(const float angle)                  { m_offsetAngle = angle; }
	

public:
	//前の角度
	static const float  FORWARD_ANGLE;
	//後ろの角度
	static const float  BACKWARD_ANGLE;
	//左の角度
	static const float  LEFT_ANGLE;
	//右の角度
	static const float  RIGHT_ANGLE;

private:
	//当たり判定モデル
	std::unique_ptr<DirectX::GeometricPrimitive>	m_WallApproachCollider;
	//当たり判定
	std::unique_ptr<BoxCollider>				    m_collider;
	//サイズ
	DirectX::SimpleMath::Vector3                    m_size;
	//所持してるキャラ
	Character*									    m_chara;
	//オフセット角度
	float                                           m_offsetAngle;
	//移動方向
	WallApproachVelID							    m_isWallApproach;

};