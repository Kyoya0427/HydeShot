//======================================================
// File Name	 : SelectState.h
// Summary		 : セレクトステイト
// Date		     : 2020/5/12
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/GameState/IGameState.h>

#include <Game/Bg/SelectBg.h>

#include <Game/UI/Button.h>

#include <Game/GameObject/SelectMode.h>

class SelectState :public IGameState
{
public:
	enum class SelectCharacter
	{
		PLAYER,
		ENEMY,

		NUM
	};

	enum class Menu
	{
		BLUE,
		SELECT,
		RED
	};

public:
	SelectState();

public:
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
	SelectMode GetBlueMode()         { return m_blueMode; }
	SelectMode GetRedMode()          { return m_redMode; }
	SelectCharacter GetSelectChara() { return m_selectChara; }

private:
	//キートラッカー
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//セレクトの背景
	std::unique_ptr<SelectBg>                           m_selectBg;
	//青キャラクターモードセレクト
	std::unique_ptr<Button>							    m_blueButton[4];
	//キャラセレクトボタン
	std::unique_ptr<Button>							    m_charaSelectButton[static_cast<int>(SelectCharacter::NUM)];
	//赤キャラクターモードセレクト
	std::unique_ptr<Button>							    m_redButton[static_cast<int>(SelectMode::NUM)];
	//青キャラクター
	SelectMode                                          m_blueMode;
	//赤キャラクターの選択
	SelectCharacter										m_selectChara;
	//赤キャラクター
	SelectMode                                          m_redMode;
	//選択中のメニュー
	Menu                                                m_menu;
	//デフォルトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//セレクトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;
};