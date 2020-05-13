//======================================================
// File Name	: ResultState.h
// Summary	: リザルトステイト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include "IGameState.h"


class ResultState :public IGameState
{
public:
	ResultState();

public:
	virtual ~ResultState();

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

