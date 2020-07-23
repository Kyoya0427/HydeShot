//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

class Search : public CharaState
{
public:
	//コンストラクタ
	Search();
public:
	//初期化
	void Initialize(Character* chara) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

protected:
	Character* m_chara;
	Search*    m_search;
};