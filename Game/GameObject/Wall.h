//======================================================
// File Name	: Wall.h
// Summary		: 壁クラス
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
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	//当たり判定のサイズを取得
	const DirectX::SimpleMath::Vector3& GetCollSize() const { return m_collSize; }
	// モデル設定関数
	void SetModel(DirectX::Model* model)                    { m_model = model; }

private:
	//テクスチャーハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	// モデルデータへのポインタ
	DirectX::Model*                                     m_model;
	//当たり判定オブジェクト
	std::unique_ptr<DirectX::GeometricPrimitive>        m_boxCollider;
	//当たり判定
	std::unique_ptr<BoxCollider>                        m_collider;
	//当たり判定のサイズ
	DirectX::SimpleMath::Vector3                        m_collSize;

};
