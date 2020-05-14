//======================================================
// File Name	: IGameObject.h
// Summary	: ゲームオブジェクト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>




class IGameObject
{
public:
	//オブジェクトの種類
	enum ObjectTag
	{
		None,
		Player,
		Enemy
	};

public:
	//コンストラクタ
	IGameObject(const ObjectTag tag = ObjectTag::None);

	//デストラクタ
	virtual ~IGameObject();

public:
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;
	//描画
	virtual void Render(const DX::StepTimer& timer) = 0;
	//当たったあとの処理
	virtual void OnCollision(IGameObject* object) = 0;

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
	//回転量を取得
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	//サイズを取得
	const DirectX::SimpleMath::Vector3& GetScale() const;
	//描画順を取得
	const int GetDrawPrio() const;
	//タグ名を登録
	void SetTag(const ObjectTag tag);
	//座標を登録
	void SetPosition(DirectX::SimpleMath::Vector3& position);
	//回転量を登録
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	//サイズを登録
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	//描画順を登録
	void SetDrawPrio(int prio);
	//非表示にする
	static void Destroy(IGameObject* object);

private:
	//true有効
	bool m_isValid;
	// 描画順序管理用(小さいほど手前に描画される）
	int m_drawPrio;
	//タグ
	ObjectTag m_tag;

	
protected:
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//ベロシティー
	DirectX::SimpleMath::Vector3 m_velocity;
	//回転
	DirectX::SimpleMath::Vector3 m_rotation;
	//サイズ
	DirectX::SimpleMath::Vector3 m_scale;
	//ワールド行列
	DirectX::SimpleMath::Matrix     m_world;

	// ステージ上の位置
	int m_x, m_y;
};




