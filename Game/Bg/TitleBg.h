//======================================================
// File Name	: TitleBg.h
// Summary		: タイトル画像
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

class TitleBg : public GameObject
{
public:
	// コンストラクタ
	TitleBg();
	//デストラクタ
	~TitleBg();

public:
	// 初期化関数
	void Initialize(const DirectX::SimpleMath::Vector3& pos);
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画関数
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	//テクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;

};