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
	InitializeTraining(L"Resources\\CSV\\test.csv");
	InitializeNeuralNetwork();
	m_error = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
	OutputDataFile("Resources\\CSV\\OutputData.csv");
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

	m_training = std::vector<std::vector<float>>(MAX_DATA_H, std::vector<float>(MAX_DATA_W, 0));

	// ステージデータの読み込み
	for (int i = 0; i < MAX_DATA_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < MAX_DATA_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_training[i][j] = std::stod(tmp);
		
		}
	}
}

/// <summary>
/// ニューラルネットワークの初期化
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// ニューラルネットワークを初期化する(入力層:3、隠れ層:60、出力層:1)
	m_neuralNetwork->Initialize(4, 20, 3);

	// 学習率を設定する
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	float	error = 1.0;
	int		count = 0;
	// 誤差逆伝播する(Back propagate)
	while (error > 0.1 && count < 1000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			//距離
			m_neuralNetwork->SetInput(0, m_training[i][0]);			
			//角度
			m_neuralNetwork->SetInput(1, m_training[i][1]);			
			//HP
			m_neuralNetwork->SetInput(2, m_training[i][2]);			
			//壁
			m_neuralNetwork->SetInput(3, m_training[i][3]);			
			
			//距離
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][4]);
			//角度
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][5]);
			//発砲
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][6]);

			//// 前方伝播する(Feed forward)
			m_neuralNetwork->FeedForward();
			//// 誤差を計算する(Calculate error)
			error += m_neuralNetwork->CalculateError();
			//// 誤差逆伝播する(Back propagate)		
			m_neuralNetwork->BackPropagate();
		}
		error = error / MAX_DATA_H;
	}
	m_error = error;
}

/// <summary>
/// 行動パターンを選択
/// </summary>
/// <param name="character">キャラ</param>
/// <param name="enemys">敵</param>
/// <returns>行動パターン</returns>
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemys)
{
	float distance = Vector3::Distance(character->GetPosition(), enemys->GetPosition());
	OutputData data;
	////距離
	//m_neuralNetwork->SetInput(0, 0);
	////角度
	//m_neuralNetwork->SetInput(1,0);
	////HP
	//m_neuralNetwork->SetInput(2, 1);
	////壁判定
	//m_neuralNetwork->SetInput(3, 1);

	//距離
	m_neuralNetwork->SetInput(0, distance / 18.0f);
	//角度
	m_neuralNetwork->SetInput(1,enemys->GetDegreeY() / 360.0f);
	//HP
	m_neuralNetwork->SetInput(2, character->GetHp() / 5);
	//敵を撃てるか判定
	m_neuralNetwork->SetInput(3, character->GetEnemySightContact());

	data.inputDis    = distance / 18.0f;
	data.inputDegree = enemys->GetDegreeY() / 360.0f;
	data.inputHp     = character->GetHp() / 5;
	data.inputShot   = character->GetEnemySightContact();

	m_neuralNetwork->FeedForward();

	float dis  = m_neuralNetwork->GetOutput(0) * 18.0f;
	float rot  = m_neuralNetwork->GetOutput(1) * 360;
	float shot = m_neuralNetwork->GetOutput(2);

	data.outputDis    = dis;
	data.outputDegree = rot;
	data.outputShot   = shot;

	m_outputData.push_back(data);

	if(dis >= 10.0f)
		return	AIController::Behavior::MOVE_FORWARD;
	if (dis <= 6.0f)
		return AIController::Behavior::MOVE_BACKWARD;

	return AIController::Behavior::NONE;
}

void NeuralNetworkManager::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 100, L"dis = %f", m_neuralNetwork->GetOutput(0) * 18.0f);
	debugFont->draw();
	debugFont->print(10, 130, L"rot = %f", m_neuralNetwork->GetOutput(1) * 360.0f);
	debugFont->draw();
	debugFont->print(10, 160, L"s = %f", m_neuralNetwork->GetOutput(2));
	debugFont->draw();

	debugFont->print(10, 190, L"error = %f", m_error * 100.0f);
	debugFont->draw();
}

void NeuralNetworkManager::OutputDataFile(char* fname)
{
	FILE* f;

	errno_t error;
	error = fopen_s(&f, fname, "w");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "A = D, B = R, C = H, D = W, E = D, F = R, G = S \n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f,\n",output.inputDis,
			output.inputDegree,output.inputHp,output.inputShot,
			output.outputDis,output.outputDegree,output.outputShot );
	}
	fclose(f);
}



