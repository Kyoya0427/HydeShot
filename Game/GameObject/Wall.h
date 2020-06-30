//======================================================
// File Name	: Wall.h
// Summary		: 壁クラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/Collider/BoxCollider.h>

#include <Game/GameObject/GameObject.h>

class Stage;

class Wall : public GameObject
{
public:
	// コンストラクタ
	Wall(const ObjectTag tag);
	// デストラクタ
	~Wall();

public:
	// 初期化関数
	void Initialize(int x, int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render() override;

	void OnCollision(GameObject* object) override;
	// モデル設定関数
	void SetModel(DirectX::Model* model);
	//当たり判定のサイズを取得
	DirectX::SimpleMath::Vector3 GetCollSize();

private:
	// モデルデータへのポインタ
	DirectX::Model* m_models;
	//当たり判定オブジェクト
	std::unique_ptr<DirectX::GeometricPrimitive> m_boxCollider;
	//当たり判定
	std::unique_ptr<BoxCollider>  m_collider;
	//当たり判定のサイズ
	DirectX::SimpleMath::Vector3  m_collSize;

};
