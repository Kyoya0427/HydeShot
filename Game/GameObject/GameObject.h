//======================================================
// File Name	: GameObject.h
// Summary		: ゲームオブジェクト
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK/SimpleMath.h>

#include <Game/Common/StepTimer.h>

#include <Game/Collider/RaycastHit.h>


class GameObject
{
public:
	//オブジェクトの種類
	enum class ObjectTag
	{
		None,

		Player,
		Enemy1,
		Enemy2,
		Bullet,
		Wall,
		Sight01,
		Sight02,
		WallApproach,
		
		NUM
	};

public:
	//コンストラクタ
	GameObject(const ObjectTag& tag = ObjectTag::None);
	//デストラクタ
	virtual ~GameObject();

public:
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;
	//描画
	virtual void Render() = 0;
	//当たったあとの処理
	virtual void OnCollision(GameObject* object) = 0;

public:
	// 無効
	void Invalidate();
	//有効
	bool IsValid() const;
	// 無効
	bool IsInvalid() const;

public:
	//タグを取得
	const ObjectTag GetTag() const                          { return m_tag; }
	//座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() const { return m_position; }
	//速度を取得
	const DirectX::SimpleMath::Vector3& GetVelocity() const { return m_velocity; }
	//回転量を取得
	const DirectX::SimpleMath::Vector3& GetRotation() const { return m_rotation; }
	//サイズを取得
	const DirectX::SimpleMath::Vector3& GetScale() const    { return m_scale; }
	//ワールド座標を取得
	const DirectX::SimpleMath::Matrix& GetWorld() const     { return m_world; }
	//色を取得
	const DirectX::SimpleMath::Color& GetColor() const      { return m_color; }
	//描画順を取得
	const int GetDrawPrio() const							{ return m_drawPrio; }
	//Y軸デグリそ取得  
	float GetRadiansY() const							    { return m_rotation.y; }
	//弾を撃ったオブジェクトのタグを取得
	ObjectTag GetCharaTag() const                           { return m_charaTag; }

public:
	//タグ名を設定
	void SetTag(const ObjectTag& tag)                              { m_tag = tag; }
	//座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	//速度を設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//回転量を設定
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	//サイズを設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale)       { m_scale = scale; }
	//色を設定
	void SetColor(const DirectX::SimpleMath::Color color)          { m_color = color; }
	//描画順を設定
	void SetDrawPrio(int drawPrio)                                 { m_drawPrio = drawPrio; }
	//弾を撃ったオブジェクトのタグを設定
	void SetCharaTag(const ObjectTag& tag)                         { m_charaTag = tag; }

public:
	//非表示にする
	static void Destroy(GameObject* object);
	
private:
	//true有効
	bool                            m_isValid;
	// 描画順序管理用(小さいほど手前に描画される）
	int                             m_drawPrio;
	
protected:
	//オブジェクトタグ名
	ObjectTag                       m_tag;
	//座標
	DirectX::SimpleMath::Vector3    m_position;
	//ベロシティー
	DirectX::SimpleMath::Vector3    m_velocity;
	//回転
	DirectX::SimpleMath::Vector3    m_rotation;
	//サイズ
	DirectX::SimpleMath::Vector3    m_scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix     m_world;
	//オブジェクトカラー
	DirectX::SimpleMath::Color      m_color;
	//ステージ上の位置
	int                             m_x, m_y;
	//半径
	float                           m_radius;
	//弾を撃ったオブジェクトのタグ名
	ObjectTag                       m_charaTag;

};

/// <summary>
/// 回転量を設定
/// </summary>
/// <param name="rotation">回転量</param>
inline void GameObject::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
{
	float radians = DirectX::XMConvertToRadians(DirectX::XMConvertToDegrees(rotation.y));
	
	if (radians > DirectX::XM_2PI)
		radians = 0.0f;
	if (radians < -DirectX::XM_2PI)
		radians = 0.0f;

	if (m_rotation.y < 0.0f)
		radians = DirectX::XM_2PI + radians;

	m_rotation = DirectX::SimpleMath::Vector3(rotation.x, radians, rotation.z);
}