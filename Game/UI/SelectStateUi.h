//======================================================
// File Name	: SelectStateUi.h
// Summary		: 選択したステイト
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

#include <Game/CharaState/CharaStateID.h>

class SelectStateUi :public GameObject
{
public:
	//コンストラクタ
	SelectStateUi();
	//デストラクタ
	~SelectStateUi();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	//ステートを設定
	void SetSelectState(wchar_t* state)  { m_selectState = state; }
	//モードを設定
	void SetSelectMode(wchar_t* mode)    { m_selectMode = mode; }

private:
	//ステート
	wchar_t*        m_selectState;
	//モード
	wchar_t*		m_selectMode;

};