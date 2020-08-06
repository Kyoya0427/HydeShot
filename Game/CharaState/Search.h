//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/CharaState/Standing.h>
#include <Game/CharaState/Forward.h>
#include <Game/CharaState/Backward.h>
#include <Game/CharaState/LeftTurn.h>
#include <Game/CharaState/RightTurn.h>

#include <Game/Controller/CharacterController.h>

class Search : public CharaState
{
public:
	//コンストラクタ
	Search();
public:
	//初期化
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

public:
	//ステイトを変更
	void ChangeStandingState();
	void ChangeForwardState();
	void ChangeBackwardState();
	void ChangeLeftTurnState();
	void ChangeRightTurnState();

private:
	//ステイト操作するキャラクター
	Character* m_chara;
	//敵キャラクター
	Character* m_enemy;
	//現在のステート
	CharaState*				      m_search;

	//Standing状態
	std::unique_ptr<Standing>     m_standing;
	//Forward状態
	std::unique_ptr<Forward>      m_forward;
	//Backward状態
	std::unique_ptr<Backward>     m_backward;	
	//LeftTurn状態
	std::unique_ptr<LeftTurn>     m_leftTurn;
	//RightTurn状態
	std::unique_ptr<RightTurn>    m_rightTurn;
};