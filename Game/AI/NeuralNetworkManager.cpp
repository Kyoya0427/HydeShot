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
	: m_isDirectLeft()
	, m_isDirectRight()
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources\\CSV\\test3.csv");
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
	m_neuralNetwork->Initialize(5, 20, 4);

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

			m_neuralNetwork->SetInput(4, m_training[i][4]);			
			
			//距離
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][5]);
			//角度
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][6]);
			//発砲
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][7]);

			m_neuralNetwork->SetDesiredOutput(3, m_training[i][8]);

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
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemy)
{
	float distance = Vector3::Distance(character->GetPosition(), enemy->GetPosition());
	OutputData data;
	
	//距離
	m_neuralNetwork->SetInput(0, distance / 18.0f);
	SearchDirection(character, enemy);
	m_neuralNetwork->SetInput(1, m_isDirectLeft);
	m_neuralNetwork->SetInput(2, m_isDirectRight);
	//HP
	m_neuralNetwork->SetInput(2, character->GetHp() / 5);
	//敵を撃てるか判定
	m_neuralNetwork->SetInput(3, character->GetEnemySightContact());

	data.inputDis    = distance / 18.0f;
	data.inputLeft   = m_isDirectLeft;
	data.inputRight  = m_isDirectRight;
	data.inputHp     = character->GetHp() / 5;
	data.inputShot   = character->GetEnemySightContact();

	m_neuralNetwork->FeedForward();

	float dis  = m_neuralNetwork->GetOutput(0) * 18.0f;
	float shot = m_neuralNetwork->GetOutput(2);

	data.outputDis    = m_neuralNetwork->GetOutput(0);
	data.outputLeft   = m_neuralNetwork->GetOutput(1);
	data.outputRight  = m_neuralNetwork->GetOutput(2);
	data.outputShot   = m_neuralNetwork->GetOutput(3);

	m_outputData.push_back(data);

	/*if(dis >= 10.0f)
		return	AIController::Behavior::MOVE_FORWARD;
	if (dis <= 6.0f)
		return AIController::Behavior::MOVE_BACKWARD;*/

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

	

	debugFont->print(10, 220, L"error = %f", p.x);
	debugFont->draw();

	if (m_isDirectLeft) 
	{
		debugFont->print(10, 250, L"left = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(10, 250, L"left = false");
		debugFont->draw();
	}

	if (m_isDirectRight)
	{
		debugFont->print(10, 280, L"right = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(10, 280, L"right = false");
		debugFont->draw();
	}
}

void NeuralNetworkManager::SearchDirection(Character* character, Character* enemy)
{
	Vector3 u;
	m_isDirectLeft = false;
	m_isDirectRight = false;

	u = Rotate(-enemy->GetRadiansY(), (character->GetPosition() - enemy->GetPosition()));
	p = u;
//	u.Normalize();
	
	if (u.x < -0.4f)
		m_isDirectLeft = true;
	else if (u.x > 0.4f)
		m_isDirectRight = true;



}

Vector3 NeuralNetworkManager::Rotate(float angle, Vector3 u)
{
	float	x, y;

	x = u.x * cos(-angle) + u.y * sin(-angle);
	y = -u.x * sin(-angle) + u.y * cos(-angle);

	return Vector3(x, 0, y);
}

void NeuralNetworkManager::OutputDataFile(char* fname)
{
	FILE* f;

	errno_t error;
	error = fopen_s(&f, fname, "w");

	fprintf(f, "--------------------------------------------------------------------------------------\n");
	fprintf(f, "A = D, B = L, C = R, D = H, E = W, F = D, G = L, H = R, I = S \n");
	fprintf(f, "--------------------------------------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f,\n",output.inputDis,
			output.inputLeft, output.inputRight,output.inputHp,output.inputShot,
			output.outputDis,output.outputLeft, output.outputRight,output.outputShot);
	}
	fclose(f);
}



