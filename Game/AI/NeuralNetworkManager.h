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
	struct OutputData
	{
		float inputDis;
		float inputLeft;
		float inputRight;
		float inputWall;
		float inputShoot;
		float inputHp;
		float outputDis;
		float outputLeft;
		float outputRight;
		float outputWall;
		float outputShoot;
		char* outputChoiceMode;
	};

public:
	//コンストラクタ
	NeuralNetworkManager();
	//デストラクタ
	virtual ~NeuralNetworkManager();

public:
	static const int MAX_DATA_H = 270;
	static const int MAX_DATA_W = 11;

public:
	//データを取得
	void InitializeTraining(wchar_t* fname);
	//ニューラルネットワークの初期化
	void InitializeNeuralNetwork();
	//行動パターンを選択
	AIController::State BehaviorSelection(Character* character, Character* enemy) override;

	void Render();

	void SearchDirection(Character* character, Character* enemy);

	DirectX::SimpleMath::Vector3 Rotate(float angle, DirectX::SimpleMath::Vector3 u);

public:
	void OutputDataFile(char* fname);

public: 
	//データを格納
	std::vector<std::vector<float>> m_training;
	//ニューラルネットワーク
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;

	float m_error;
	Character* m_character;

	OutputData					   m_data;
	std::vector<OutputData>        m_outputData;

	bool                          m_isDirectLeft;
	bool                          m_isDirectRight;
	float                         m_p;
};

