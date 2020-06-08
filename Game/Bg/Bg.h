//======================================================
// File Name	: Bg.h
// Summary		: 背景
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\Model.h>

#include <Game\GameObject\GameObject.h>

class GameWindow;

class Bg : public GameObject
{
public:
	// コンストラクタ
	Bg();
	//デストラクタ
	~Bg();

public:
	// 初期化関数
	void Initialize();
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	// ゲームウインドウへのポインタ
	GameWindow* m_gameWindow;
	// モデルデータへのポインタ
	std::unique_ptr<DirectX::Model> m_model;
	// 回転角
	float m_angle;
};