//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

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
	//デストラクタ
	~Search();

public:
	//初期化
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;

public:
	//ステイトを変更
	void ChangeForwardState()   { m_search = static_cast<CharaState*>(m_forward.get());   }
	void ChangeBackwardState()  { m_search = static_cast<CharaState*>(m_backward.get());  }
	void ChangeLeftTurnState()  { m_search = static_cast<CharaState*>(m_leftTurn.get());  }
	void ChangeRightTurnState() { m_search = static_cast<CharaState*>(m_rightTurn.get()); }

private:
	//ステイト操作するキャラクター
	Character*                    m_chara;
	//敵キャラクター
	Character*                    m_enemy;
	//現在のステート
	CharaState*				      m_search;
	//Forward状態
	std::unique_ptr<Forward>      m_forward;
	//Backward状態
	std::unique_ptr<Backward>     m_backward;	
	//LeftTurn状態
	std::unique_ptr<LeftTurn>     m_leftTurn;
	//RightTurn状態
	std::unique_ptr<RightTurn>    m_rightTurn;

};