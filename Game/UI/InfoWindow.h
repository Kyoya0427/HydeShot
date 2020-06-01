#pragma once

#include <DirectXTK\SpriteBatch.h>

#include <Game\GameObject\GameObject.h>

#include <Game\UI\Blink.h>
#include <Game\UI\Letter.h>





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

	void Initialize();
	 void Update(const DX::StepTimer & timer) override;
	 void Render() override;
	 void HitContact(GameObject* object) override;

private:
	//テクスチャーハンドル（背景）
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bg01Texture;

};