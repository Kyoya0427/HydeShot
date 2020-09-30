//======================================================
// File Name	 : SelectState.h
// Summary		 : セレクトステイト

// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/GameState/IGameState.h>

#include <Game/Bg/SelectBg.h>

#include <Game/UI/Button.h>
#include <Game/UI/OptionList.h>

#include <Game/GameObject/SelectMode.h>

class Blink;

class SelectState :public IGameState
{
public:
	enum class SelectCharacter
	{
		ENEMY,
		PLAYER,
		
		NUM
	};
public:
	//コンストラクタ
	SelectState();
	//デストラクタ
	~SelectState();

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
	static SelectMode GetBlueMode()         { return m_blueMode; }
	static SelectMode GetRedMode()          { return m_redMode; }
	static SelectCharacter GetSelectChara() { return m_selectChara; }

public:
	//青キャラクター
	static SelectMode                                   m_blueMode;
	//赤キャラクターの選択
	static SelectCharacter								m_selectChara;
	//赤キャラクター
	static SelectMode                                   m_redMode;

public:
	//赤キャラクターモードセレクト
	void ChangeRedMode()  { m_currentOption = m_redOption.get(); }
	//青キャラクターモードセレクト
	void ChangeBlueMode() { m_currentOption = m_blueOption.get(); }
	//赤のモードリストに追加
	void AddRedMode();
private:
	//デフォルトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//セレクトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;	
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_redTexture;	
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_blueTexture;
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_redCharaTexture;
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_blueCharaTexture;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>               m_spriteBatch;
	//キートラッカー
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//セレクトの背景
	std::unique_ptr<SelectBg>                           m_selectBg;
	//モードを選択
	std::unique_ptr<OptionList>						    m_selectMode;
	//赤キャラクターモードセレクト
	std::unique_ptr<OptionList>							m_redOption;
	//青キャラクターモードセレクト
	std::unique_ptr<OptionList>							m_blueOption;
	//操作中のモードリスト
	OptionList*                                         m_currentOption;
	//モードを選択しているか
	bool												m_isSelectMode;
	//ブリンク
	std::unique_ptr<Blink>                              m_blink;
	//赤を選択中
	bool                                                m_isRedSelect;
};