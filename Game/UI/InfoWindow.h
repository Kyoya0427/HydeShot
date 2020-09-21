//======================================================
// File Name	: InfoWindow.h
// Summary		: 情報ウィンドウ
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SpriteBatch.h>

#include <Game\GameObject\GameObject.h>

class NeuralNetworkData;
class UiBg;
class SelectStateUi;
class HpUi;

class InfoWindow :public GameObject
{
public:
	//画面サイズ
	static constexpr int SCREEN_W = 1280 - 960;
	static constexpr int SCREEN_H = 720;
	
public:
	//コンストラクタ
	InfoWindow();
	//デストラクタ
	~InfoWindow();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer & timer) override;
	//描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	//テクスチャーハンドル（背景）
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bg01Texture;
	//ニューラルネットワークのデータ
	std::unique_ptr<NeuralNetworkData>				 m_neuralNetworkData;
	//UI背景
	std::unique_ptr<UiBg>							 m_uiBg;
	//選択したステイト
	SelectStateUi*									 m_selectState;
	//キャラクターのHp
	HpUi*			                                 m_character;
};