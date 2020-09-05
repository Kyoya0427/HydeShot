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

class InfoWindow :public GameObject
{
public:
	//画面サイズ
	static constexpr int SCREEN_W = 1280 - 960;
	static constexpr int SCREEN_H = 720;
	
	//１グリット
	static constexpr int GRIT_SIZE = 24;
public:
	//コンストラクタ
	InfoWindow();
	~InfoWindow();

public:
	void Initialize();
	void Update(const DX::StepTimer & timer) override;
	void Render() override;
	void OnCollision(GameObject* object) override;

private:
	//テクスチャーハンドル（背景）
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bg01Texture;

	std::unique_ptr<NeuralNetworkData>				 m_neuralNetworkData;
	std::unique_ptr<UiBg>							 m_uiBg;
	SelectStateUi*									 m_selectState;
};