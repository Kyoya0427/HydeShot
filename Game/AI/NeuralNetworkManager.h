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
	//外部出力データ
	struct OutputData
	{
		float inputDis;
		float inputLeft;
		float inputRight;
		float inputWall;
		float inputShoot;
		float outputDis;
		float outputLeft;
		float outputRight;
		float outputWall;
		float outputShoot;
		char* outputChoiceMode;
	};

public:
	//コンストラクタ
	NeuralNetworkManager(Character* character, Character* enemy);
	//デストラクタ
	virtual ~NeuralNetworkManager();

public:
	//データの数
	static const int MAX_DATA_H = 54;
	static const int MAX_DATA_W = 10;

public:
	//データを取得
	void InitializeTraining(wchar_t* fname);
	//ニューラルネットワークの初期化
	void InitializeNeuralNetwork();
	//行動パターンを選択
	CharaStateID BehaviorSelection() override;
	//描画
	void Render();
	//左右判定
	void SearchDirection(Character* character, Character* enemy);
	// 内積計算
	DirectX::SimpleMath::Vector3 Rotate(float angle, const DirectX::SimpleMath::Vector3& u);

public:
	// 入力と出力の値を外部に出力
	void OutputDataFile(char* fname);

public: 
	//データを格納
	std::vector<std::vector<float>>  m_training;
	//ニューラルネットワーク
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
	//自機
	Character*                       m_character;
	//敵
	Character*                       m_enemy;

	//計算時のデータ
	OutputData					     m_data;
	//全ての計算データ
	std::vector<OutputData>          m_outputData;
	//計算時のエラー数
	float                            m_error;
	//左側にいる
	bool                             m_isDirectionLeft;
	//右側にいる
	bool                             m_isDirectionRight;
	//距離
	float                            m_distance;
};

