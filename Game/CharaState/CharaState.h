//======================================================
// File Name	: CharaState.h
// Summary		: キャラのステート
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
	//コンストラクタ
	CharaState()
		: m_neuralNetwork()
		, m_chara()
		, m_enemy()
	{
	};
	//デストラクタ
	virtual ~CharaState() = default;

public:
	//初期化
	virtual void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) = 0;
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;

public:
	NeuralNetworkManager* GetNeuralNetworkManager() { return m_neuralNetwork; }
	Character* GetChara() { return m_chara; }
	Character* GetEnemy() { return m_enemy; }

public:
	void SetNeuralNetworkManager(NeuralNetworkManager* neuralNetworkManager) { m_neuralNetwork = neuralNetworkManager; }
	void SetChara(Character* chara) { m_chara = chara; }
	void SetEnemy(Character* enemy) { m_enemy = enemy; }

private:
	//ニューラルネットワークマネージャー
	NeuralNetworkManager*		m_neuralNetwork;
	//ステイト操作するキャラクター
	Character*                  m_chara;
	//敵キャラクター
	Character*                  m_enemy;
};