//======================================================
// File Name	 : OptionList.h
// Summary		 : 選択肢リスト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Common/StepTimer.h>

class Button;

class OptionList
{
public:
	//コンストラクタ
	OptionList();
	//デストラクタ
	~OptionList();

public:
	//描画
	void Render();
	//追加
	void Add(DirectX::SimpleMath::Vector2 pos, wchar_t* letter);
	//現在より一つ上に上げる
	void CurrentUp();
	//現在より一つ下に下げる
	void CurrentDown();

public:
	//現在の選択を取得
	int GetCurrent() { return m_current; }
	//テクスチャーを設定
	void SetTexture(ID3D11ShaderResourceView* default, ID3D11ShaderResourceView* select);

private:
	//現在の選択肢
	unsigned int						   m_current;
	//ボタン
	std::vector<std::unique_ptr<Button>>   m_button;
	//デフォルトテクスチャー
	ID3D11ShaderResourceView*              m_defaultTexture;
	//セレクトテクスチャー
	ID3D11ShaderResourceView*              m_selectTexture;

};
