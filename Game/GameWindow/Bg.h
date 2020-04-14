//======================================================
// File Name	: Bg.h
// Summary	: 背景クラス
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>
#include <DirectXTK\Model.h>

class GameWindow;

class Bg : public IGameObject
{
	// ゲームウインドウへのポインタ
	GameWindow* m_gameWindow;

	// モデルデータへのポインタ
	std::unique_ptr<DirectX::Model> m_model;

	// 回転角
	float m_angle;

public:
	// コンストラクタ
	Bg();
	
	// 初期化関数
	void Initialize();

	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render(const DX::StepTimer& timer) override;

	void OnCollision(IGameObject* object) override;
};