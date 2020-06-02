//======================================================
// File Name	 : TitleState.h
// Summary	 : タイトルステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\GameState\IGameState.h>


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
	void Render() override;
	//終了
	void Finalize() override;



private:
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;


};

