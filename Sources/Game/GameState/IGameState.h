//======================================================
// File Name	 : IGameState.h
// Summary	 : ゲームステイトのインターフェイス
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once
#include <Framework\StepTimer.h>

class IGameState
{
public:
	IGameState() = default;

public:
	virtual ~IGameState() = default;

public:
	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;
	//描画
	virtual void Render(const DX::StepTimer& timer) = 0;
	//終了
	virtual void Finalize() = 0;
};