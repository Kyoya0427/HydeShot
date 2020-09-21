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

#include <Game\UI\Blink.h>

class ResultBg;

class ResultState :public IGameState
{
public:
	//コンストラクタ
	ResultState();
	//デストラクタ
	 ~ResultState();

public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//終了
	void Finalize() override;

public:
	static bool		 m_isPlayerWin;

private:
	//キートラッカー
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	//リザルト背景
	std::unique_ptr<ResultBg>                        m_resultBg;
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;
	//テクスチャー座標
	DirectX::SimpleMath::Vector2                     m_pushPos;
	//ブリンク
	std::unique_ptr<Blink>                           m_blink;
	//ブリンクを使用するか
	bool                                             m_isBlink;

};