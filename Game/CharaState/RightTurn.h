//======================================================
// File Name	: RightTurn.h
// Summary		: 右回転ステート
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class RightTurn : public CharaState
{
public:
	//コンストラクタ
	RightTurn();
	//デストラクタ
	~RightTurn();
public:
	//初期化
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//更新
	void Update(const DX::StepTimer& timer) override;

};