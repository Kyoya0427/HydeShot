//======================================================
// File Name	: TitleState.h
// Summary		: タイトルステイト
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\GameState\IGameState.h>

class TitleBg;
class Button;

class TitleState :public IGameState
{
	enum class SelectButtton
	{
		Play,
		Exit
	};
public:
	//コンストラクタ
	TitleState();
	//デストラクタ
	 ~TitleState();

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
	//キートラッカー
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//タイトルの背景
	std::unique_ptr<TitleBg>                            m_titleBg;
	//プレイボタン
	std::unique_ptr<Button>							    m_playButton;
	//イグジットボタン
	std::unique_ptr<Button>							    m_exitButton;
	//現在のセレクトボタン
	SelectButtton                                       m_selectButton;
	//デフォルトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//セレクトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;
};