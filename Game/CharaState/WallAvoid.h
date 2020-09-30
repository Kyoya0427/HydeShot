//======================================================
// File Name	: WallAvoid.h
// Summary		: 壁回避ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/CharaState/Forward.h>
#include <Game/CharaState/Backward.h>
#include <Game/CharaState/Leftward.h>
#include <Game/CharaState/Rightward.h>

#include <Game/Controller/CharacterController.h>

class WallAvoid : public CharaState
{
public:
	//コンストラクタ
	WallAvoid();

public:
	//初期化
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	
public:
	//ステイトを変更
	void ChangeForwardState()   { m_wallAvoid = static_cast<CharaState*>(m_forward.get());   }
	void ChangeBackwardState()  { m_wallAvoid = static_cast<CharaState*>(m_backward.get());  }
	void ChangeLeftwardState()  { m_wallAvoid = static_cast<CharaState*>(m_leftward.get());  }
	void ChangeRightwardState() { m_wallAvoid = static_cast<CharaState*>(m_rightward.get()); }

private:
	//ステイト操作するキャラクター
	Character*                      m_chara;
	//敵キャラクター
	Character*                      m_enemy;
	//現在のステート
	CharaState*                     m_wallAvoid;

	//Forward状態
	std::unique_ptr<Forward>		m_forward;
	//Backward状態
	std::unique_ptr<Backward>		m_backward;
	//Leftward状態
	std::unique_ptr<Leftward>		m_leftward;
	//Rightward状態
	std::unique_ptr<Rightward>      m_rightward;

};