//======================================================
// File Name	 : PauseState.h
// Summary	 : ポーズステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"

class PauseState :public IGameState
{
public:
	PauseState();

public:
	virtual ~PauseState();

public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;
	//終了
	void Finalize() override;
};

