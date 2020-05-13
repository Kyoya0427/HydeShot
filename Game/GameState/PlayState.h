//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


#include "IGameState.h"

class GameWindow;
class InfoWindow;
class ObjectManager;

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

public: 
	//ポーズ画面に行く処理
	void ChangePauseState();

private:
	// ゲーム画面のビューポート
	D3D11_VIEWPORT                          m_viewportGame;
	// 情報画面のビューポート
	D3D11_VIEWPORT                          m_viewportInfo;
	// 情報ウィンドウ
	std::unique_ptr<InfoWindow>             m_infoWindow;
	//ゲームウィンドウ
	std::unique_ptr<GameWindow>				m_gameWindow;
	// ゲームオブジェクトマネージャー
	std::unique_ptr<ObjectManager>          m_objectManager;
};

