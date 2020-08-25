//======================================================
// File Name	: Button.h
// Summary		: UIボタン
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Common/StepTimer.h>

class Button
{
public:
	Button();
	~Button();

public:
	// 初期化関数
	void Initialize(const DirectX::SimpleMath::Vector2& pos, wchar_t* letter);
	// 更新
	void Update(const DX::StepTimer& timer);
	// 描画関数
	void Render();
	//当たった後の処理
	

public:
	void SetSelect(const bool select) { m_isSelect = select; }
	void SetDefaultTexture(ID3D11ShaderResourceView* texture) { m_defaultTexture = texture; }
	void SetSelectTexture(ID3D11ShaderResourceView* texture)  { m_selectTexture = texture; }

private:
	//デフォルトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defaultTexture;
	//セレクトテクスチャー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectTexture;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	//画像選択用
	bool											 m_isSelect;
	//ボタンの文字
	wchar_t*                                         m_letter;

	DirectX::SimpleMath::Vector2                     m_position;
};

