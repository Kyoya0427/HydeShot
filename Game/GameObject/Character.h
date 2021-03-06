//======================================================
// File Name	: Character.h
// Summary		: キャラクター
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/GeometricPrimitive.h>
#include <DirectXTK/Model.h>

#include <Game/GameObject/GameObject.h>

#include <Game/Common/StepTimer.h>

#include <Game/Collider/SphereCollider.h>

#include <Game/CharaState/CharaStateID.h>

#include <Game/UI/Blink.h>

class Sight;
class WallApproach;

class Character : public GameObject
{
public:
	//コンストラク
	Character(const ObjectTag tag = ObjectTag::None);
	//デストラクタ
	~Character();

public:
	// 初期化関数
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	//前進
	void Forward(const float speed)   { SetVelocityZ(-speed); }
	//後進
	void Backward(const float speed)  { SetVelocityZ(speed);  }
	//左に進む
	void Leftward (const float speed) { SetVelocityX(-speed); }
	//右に進む
	void Rightward(const float speed) { SetVelocityX(speed);  }
	//左に旋回
	void LeftTurn (const float speed) { SetRotationY(GetRotation().y + speed); }
	//右に旋回
	void RightTurn(const float speed) { SetRotationY(GetRotation().y - speed); }
	//発砲
	void Shoot();
	//HP関連の処理
	void HpProcessing(float elapsedTime);

public:
	//hpを取得
	const int  GetHp() const                           { return m_hp; }
	//壁に接触してるかを取得
	const bool GetWallContact() const                  { return m_isWallContact; }
	//壁にセンサーが接触してるかを取得
	const bool GetWallSightContact() const             { return m_isWallSightContact; }
	//敵にセンサーが接触しているかを取得
	const bool GetEnemySightContact() const            { return m_isEnemySightContact; }
	//現在のステートを取得
	const CharaStateID& GetCharaState() const          { return m_state; }
	//移動方向壁センサーを取得
	WallApproach* GetWallApproachVel() const           { return m_wallApproachVel.get(); }
	//壁発見を取得
	const bool GetWallDiscovery() const                { return m_isWallDiscovery; }
	
public:	
	//壁発見設定
	void SetWallDiscovery(const bool wallFlont)       { m_isWallDiscovery = wallFlont; }
	//壁にセンサーが接触してるか設定
	void SetWallSightContact(const bool contact)      { m_isWallSightContact = contact; }
	//敵にセンサーが接触しているか設定
	void SetEnemySightContact(const bool contact)     { m_isEnemySightContact = contact; }
	//現在のステートを設定
	void SetCharaState(const CharaStateID& state)     { m_state = state; }
	// モデル設定関数
	void SetModel(DirectX::Model* model)              { m_charaModel = model; }

public:
	//最大HP
	static const int   MAX_HP;
	static const float INVINCIBLE_TIME;
	static const float RADIUS;
	static const float SCALE;

private:
	//当たり判定モデル
	std::unique_ptr<DirectX::GeometricPrimitive>    m_sphereCollider;
	//弾モデル
	std::unique_ptr<DirectX::GeometricPrimitive>    m_bulletModel;
	//射程
	std::unique_ptr<Sight>                          m_sight;
	//壁に接近しているか(前方)
	std::unique_ptr<WallApproach>                   m_wallApproach;
	//壁に接近しているか(移動方向)
	std::unique_ptr<WallApproach>                   m_wallApproachVel;
	//当たり判定
	std::unique_ptr<SphereCollider>                 m_collider;
	//現在のステート
	CharaStateID								    m_state;
	//ブリンク
	std::unique_ptr<Blink>                          m_blink;
	//ブリンクカラー
	DirectX::SimpleMath::Color                      m_blinkColor;
	//デフォルトカラー
	DirectX::SimpleMath::Color                      m_defaultColor;
	//１フレーム前の座標
	DirectX::SimpleMath::Vector3                    m_previousPos;
	//キャラクターのモデル
	DirectX::Model*									m_charaModel;
	//壁にセンサーが接触してるか
	bool                                            m_isWallSightContact;
	//壁に接触してるか
	bool										    m_isWallContact;
	//敵にセンサーが接触しているか
	bool                                            m_isEnemySightContact;
	//壁発見
	bool										    m_isWallDiscovery;
	//ダメージ（無敵中）
	bool                                            m_isDamage;
	//HP
	int                                             m_hp;
	//無敵時間
	float                                           m_invincibleTime;

};