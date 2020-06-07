//======================================================
// File Name	: ResultState.h
// Summary		: リザルトステイト
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SimpleMath.h>	
#include <DirectXTK\Keyboard.h>

#include <Game\GameState\IGameState.h>

class ResultState :public IGameState
{
public:
	ResultState();
	virtual ~ResultState();

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

