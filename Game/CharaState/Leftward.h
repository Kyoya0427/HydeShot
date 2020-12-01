//======================================================
// File Name	: Leftward.h
// Summary		: 左移動ステート
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/CharaState/CharaState.h>

#include <Game/Controller/CharacterController.h>

class Leftward : public CharaState
{
public:
	//コンストラクタ
	Leftward();
	//デストラクタ
	~Leftward();

public:
	//初期化
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//更新
	void Update(const DX::StepTimer& timer) override;

};