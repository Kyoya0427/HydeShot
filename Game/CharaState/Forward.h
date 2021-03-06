//======================================================
// File Name	: Forward.h
// Summary		: 前移動ステート
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
	void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) override;
	//更新
	void Update(const DX::StepTimer& timer) override;

};