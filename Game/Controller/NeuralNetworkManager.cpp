//======================================================
// File Name	: NeuralNetworkManager.cpp
// Summary		: ニューラルネットワークでモード選択
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "NeuralNetworkManager.h"

#include <fstream>
#include <sstream>
#include <string>

#include <Game/Common/DebugFont.h>

#include <Game/AI/NeuralNetwork.h>

#include <Game/GameObject/Character.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
NeuralNetworkManager::NeuralNetworkManager()
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources\\CSV\\TrainingSet.csv");
	InitializeNeuralNetwork();
}

/// <summary>
/// デストラクタ
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
}

/// <summary>
/// データを取得
/// </summary>
/// <param name="fname">ファイルネーム</param>
void NeuralNetworkManager::InitializeTraining(wchar_t* fname)
{
	std::wstring str;
	// ファイルのオープン
	std::wifstream ifs(fname);

	m_training = std::vector<std::vector<double>>(MAX_DATA_H, std::vector<double>(MAX_DATA_W, 0));

	// ステージデータの読み込み
	for (int i = 0; i < MAX_DATA_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < MAX_DATA_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_training[i][j] = std::stoi(tmp);
		
		}
	}
}

/// <summary>
/// ニューラルネットワークの初期化
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// ニューラルネットワークを初期化する(入力層:3、隠れ層:60、出力層:1)
	m_neuralNetwork->Initialize(3, 40, 1);

	// 学習率を設定する
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	double	error = 1.0;
	int		count = 0;
	// 誤差逆伝播する(Back propagate)
	while (error > 0.01 && count < 100)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			m_neuralNetwork->SetInput(0, m_training[i][0] / 13);			//X距離
			m_neuralNetwork->SetInput(1, m_training[i][1] / 13);			//Y距離
			m_neuralNetwork->SetInput(2, m_training[i][2] /  5);			//HP

			m_neuralNetwork->SetDesiredOutput(0, m_training[i][3] /7);	//行動選択

			//// 前方伝播する(Feed forward)
			m_neuralNetwork->FeedForward();
			//// 誤差を計算する(Calculate error)
			error += m_neuralNetwork->CalculateError();
			//// 誤差逆伝播する(Back propagate)		
			m_neuralNetwork->BackPropagate();
		}
		error = error / MAX_DATA_H;
	}
}

/// <summary>
/// 行動パターンを選択
/// </summary>
/// <param name="character">キャラ</param>
/// <param name="enemys">敵</param>
/// <returns>行動パターン</returns>
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemys)
{
	Vector3 chara = character->GetPosition();
	Vector3 enemy = enemys->GetPosition();
	float x = chara.x - enemy.x;
	float z = chara.z - enemy.z;

	m_neuralNetwork->SetInput(0, x /13);
	m_neuralNetwork->SetInput(1, z /13);
	m_neuralNetwork->SetInput(2, character->GetHp() / 5);
	m_neuralNetwork->FeedForward();

	return static_cast<AIController::Behavior>(static_cast<int>(m_neuralNetwork->GetOutput(0) * 7));
}

