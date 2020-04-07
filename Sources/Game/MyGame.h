//======================================================
// File Name	: MyGame.h
// Summary	: マイゲーム
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>


#include <Framework\Game.h>

class GameStateManager;

class MyGame
{
public:
	//コンストラクタ
	MyGame();
	//デストラクタ
	~MyGame();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer);
	//描画
	void Render(const DX::StepTimer& timer);
	//終了
	void Finalize();

private:
	//ステイトマネジャー
	std::unique_ptr<GameStateManager>          m_stateManager;
};