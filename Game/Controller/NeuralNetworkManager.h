//======================================================
// File Name	: NeuralNetworkManager.h
// Summary		: ニューラルネットワークでモード選択
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/Controller/AIController.h>

class NeuralNetwork;
class Character;

class NeuralNetworkManager
{
public:
	//コンストラクタ
	NeuralNetworkManager();
	//デストラクタ
	~NeuralNetworkManager();

public:
	static const int MAX_DATA_H = 3920; 
	static const int MAX_DATA_W = 4; 

public:
	//データを取得
	void InitializeTraining(wchar_t* fname);
	//ニューラルネットワークの初期化
	void InitializeNeuralNetwork();
	//行動パターンを選択
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys);

public: 
	//データを格納
	std::vector<std::vector<double>> m_training;
	//ニューラルネットワーク
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
};

