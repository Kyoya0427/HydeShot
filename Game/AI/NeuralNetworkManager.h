//======================================================
// File Name	: NeuralNetworkManager.h
// Summary		: ニューラルネットワークでモード選択
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/AI/Ai.h>

class NeuralNetwork;

class NeuralNetworkManager : public Ai
{
public:
	//コンストラクタ
	NeuralNetworkManager();
	//デストラクタ
	virtual ~NeuralNetworkManager();

public:
	static const int MAX_DATA_H = 3920; 
	static const int MAX_DATA_W = 4; 
//	static const int MAX_DATA_H = 301;
//	static const int MAX_DATA_W = 7;
public:
	//データを取得
	void InitializeTraining(wchar_t* fname);
	//ニューラルネットワークの初期化
	void InitializeNeuralNetwork();
	//行動パターンを選択
	AIController::Behavior BehaviorSelection(Character* character, Character* enemys) override;

public: 
	//データを格納
	std::vector<std::vector<double>> m_training;
	//ニューラルネットワーク
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
};

