//======================================================
// File Name	: CharaState.h
// Summary		: キャラのステート
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/Character.h>

#include <Game/Common/StepTimer.h>

class Character;
class CharacterController;
class NeuralNetworkManager;

class CharaState
{
public:
	//デストラクタ
	virtual ~CharaState() = default;

public:
	//初期化
	virtual void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) = 0;
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;

protected:

	NeuralNetworkManager*		m_neuralNetwork;
};