//======================================================
// File Name	: WallAvoid.h
// Summary		: 壁回避ステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

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
	void Initialize(Character* chara, Character* enemy) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;

public:
	void ChangeLeftwardState();
	void ChangeRightwardState();

private:
	Character*                      m_chara;
	Character*						m_enemy;
	CharaState*						m_wallAvoid;

	std::unique_ptr<Leftward>		m_leftward;
	std::unique_ptr<Rightward>      m_rightward;
};