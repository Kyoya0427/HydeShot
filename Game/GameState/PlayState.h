//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
//======================================================
#pragma once


#include "IGameState.h"



class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

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

