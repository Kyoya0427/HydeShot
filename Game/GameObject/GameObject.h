//======================================================
// File Name	: GameObject.h
// Summary		: ゲームオブジェクト
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>

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
		Flag_01,
		Flag_02,
		Sight01,
		Sight02,


		NUM
	};

public:
	//コンストラクタ
	GameObject(const ObjectTag tag = ObjectTag::None);

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
	//タグを取得
	const ObjectTag GetTag() const;
	//座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	//速度を取得
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	//回転量を取得
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	//サイズを取得
	const DirectX::SimpleMath::Vector3& GetScale() const;
	//色を登録
	DirectX::SimpleMath::Color GetColor();
	//描画順を取得
	const int GetDrawPrio() const;
	//当たり判定の球の半径
	float GetRadius();
	//弾を撃ったオブジェクトのタグを取得
	ObjectTag GetCharaTag();

public:
	//タグ名を登録
	void SetTag(const ObjectTag tag);
	//座標を登録
	void SetPosition(DirectX::SimpleMath::Vector3 position);
	//速度を登録
	void SetVelocity(DirectX::SimpleMath::Vector3 velocity);
	//回転量を登録
	void SetRotation(DirectX::SimpleMath::Vector3 rotation);
	//サイズを登録
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	//色を登録
	void SetColor(DirectX::SimpleMath::Color color);
	//描画順を登録
	void SetDrawPrio(int prio);
	//弾を撃ったオブジェクトのタグを設定
	void SetCharaTag(ObjectTag tag);
	//非表示にする
	static void Destroy(GameObject* object);
	
private:
	//true有効
	bool m_isValid;
	// 描画順序管理用(小さいほど手前に描画される）
	int m_drawPrio;
	
	
protected:
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
	int m_x, m_y;
	//半径
	float  m_radius;
	//オブジェクトタグ名
	ObjectTag m_tag;
	//弾を撃ったオブジェクトのタグ名
	ObjectTag           m_charaTag;
};
