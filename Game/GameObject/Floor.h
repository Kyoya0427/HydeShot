//======================================================
// File Name	: Floor.h
// Summary		: 床クラス
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\Model.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\GameObject\GameObject.h>

class Stage;

class Floor : public GameObject
{	
private:
	// モデルデータへのポインタ
	DirectX::Model* m_models;

public:
	// コンストラクタ
	Floor();

public:
	// 初期化関数
	void Initialize(int x, int y);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

	// モデル設定関数
	void SetModel(DirectX::Model* model);

};
