//======================================================
// File Name	: IGameState.h
// Summary		: ゲームステイトの基底クラス
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\Common\StepTimer.h>

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
	virtual void Render() = 0;
	//終了
	virtual void Finalize() = 0;

};