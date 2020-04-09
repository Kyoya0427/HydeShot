//======================================================
// File Name	 : TitleState.h
// Summary	 : タイトルステイト
//======================================================
#pragma once

#include "IGameState.h"


class TitleState :public IGameState
{
public:
	TitleState();

public:
	virtual ~TitleState();

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

