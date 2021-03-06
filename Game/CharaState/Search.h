//======================================================
// File Name	: Search.h
// Summary		: サーチのステート
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
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//行動を選択
	void ChooseAction();

public:
	//ステイトを変更
	void ChangeForwardState()   { m_search = m_forward.get();   }
	void ChangeBackwardState()  { m_search = m_backward.get();  }
	void ChangeLeftTurnState()  { m_search = m_leftTurn.get();  }
	void ChangeRightTurnState() { m_search = m_rightTurn.get(); }

private:
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