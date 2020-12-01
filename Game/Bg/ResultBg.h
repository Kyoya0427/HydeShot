//======================================================
// File Name	: ResultBg.h
// Summary		: リザルト背景
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

class GameWindow;

class ResultBg : public GameObject
{
public:
	// コンストラクタ
	ResultBg();
	//デストラクタ
	~ResultBg();

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
	//デフォルトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winTexture;
	//セレクトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_loseTexture;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;

};