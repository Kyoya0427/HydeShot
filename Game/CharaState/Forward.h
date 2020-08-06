//======================================================
// File Name	: Forward.h
// Summary		: 前移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Forward : public CharaState
{
public:
	//コンストラクタ
	Forward();
	//デストラクタ
	~Forward();
public:
	//初期化
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

private:
	//ステイト操作するキャラクター
	Character* m_chara;
	//敵キャラクター
	Character* m_enemy;

};