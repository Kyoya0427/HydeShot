//======================================================
// File Name	: Backward.h
// Summary		: 後ろ移動ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Backward : public CharaState
{
public:
	//コンストラクタ
	Backward();
	//デストラクタ
	~Backward();
public:
	//初期化
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

private:
	Character*           m_chara;
	Character*			 m_enemy;

};