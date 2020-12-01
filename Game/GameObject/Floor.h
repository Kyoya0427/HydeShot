//======================================================
// File Name	: Floor.h
// Summary		: 床クラス
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/GameObject/GameObject.h>

class Stage;

class Floor : public GameObject
{	
public:
	// コンストラクタ
	Floor();

public:
	// 初期化関数
	void Initialize(const int x, const int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	// モデル設定関数
	void SetModel(DirectX::Model* model) { m_model = model; }

private:
	// モデルデータへのポインタ
	DirectX::Model*			m_model;

};
