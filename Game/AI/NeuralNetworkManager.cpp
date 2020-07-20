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
			m_training[i][j] = std::stof(tmp);
		
		}
	}
}

/// <summary>
/// ニューラルネットワークの初期化
/// </summary>
void NeuralNetworkManager::InitializeNeuralNetwork()
{
	// ニューラルネットワークを初期化する(入力層:5、隠れ層:40、出力層:4)
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
	while (error > 0.01 && count < 10000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			//距離
			m_neuralNetwork->SetInput(0, m_training[i][0]);			
			//左判定
			m_neuralNetwork->SetInput(1, m_training[i][1]);			
			//右判定
			m_neuralNetwork->SetInput(2, m_training[i][2]);			
			//HP
			m_neuralNetwork->SetInput(3, m_training[i][3]);		
			//壁
			m_neuralNetwork->SetInput(4, m_training[i][4]);			
			
			//距離
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][5]);
			//左判定
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][6]);
			//右判定
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][7]);
			//発砲
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
/// <param name="character">自機</param>
/// <param name="enemys">敵</param>
/// <returns>行動パターン</returns>
AIController::Behavior NeuralNetworkManager::BehaviorSelection(Character* character, Character* enemy)
{
	m_character = character;
	//距離計算
	float distance = Vector3::Distance(character->GetPosition(), enemy->GetPosition());
	m_p = distance;
	//左右判定
	SearchDirection(character, enemy);
	//距離
	m_neuralNetwork->SetInput(0, distance / 18.0f);
	//左判定
	m_neuralNetwork->SetInput(1, static_cast<float>(m_isDirectLeft));
	//右判定
	m_neuralNetwork->SetInput(2, static_cast<float>(m_isDirectRight));
	//敵を撃てるか判定
	m_neuralNetwork->SetInput(3, static_cast<float>(character->GetEnemySightContact()));
	//HP
	m_neuralNetwork->SetInput(4, static_cast<float>(character->GetHp() / 5));


	//計算開始
	m_neuralNetwork->FeedForward();

		//外部にデータ出力する為に保管
	OutputData data;

	data.inputDis      = distance / 18.0f;
	data.inputLeft     = static_cast<float>(m_isDirectLeft);
	data.inputRight    = static_cast<float>(m_isDirectRight);
	data.inputHp       = static_cast<float>(character->GetHp() / 5);
	data.inputShoot    = static_cast<float>(character->GetEnemySightContact());

	data.outputDis     = m_neuralNetwork->GetOutput(0);
	data.outputLeft    = m_neuralNetwork->GetOutput(1);
	data.outputRight   = m_neuralNetwork->GetOutput(2);
	data.outputShoot   = m_neuralNetwork->GetOutput(3);

	
	float dis   = m_neuralNetwork->GetOutput(0);
	float left  = m_neuralNetwork->GetOutput(1);
	float right = m_neuralNetwork->GetOutput(2);
	float shot  = m_neuralNetwork->GetOutput(3);

	if (shot >= 0.6f)
	{
		data.outputChoiceMode = "shoot";
		m_outputData.push_back(data);
		return	AIController::Behavior::SHOOT;
	}
	else if (left >= 0.6f)
	{
		data.outputChoiceMode = "left";
		m_outputData.push_back(data);
		return AIController::Behavior::TURN_LEFT;
	}
	else if (right >= 0.6f)
	{
		data.outputChoiceMode = "right";
		m_outputData.push_back(data);
		return AIController::Behavior::TURN_RIGHT;
	}
	else if (dis >= 0.5f)
	{
		data.outputChoiceMode = "forward";
		m_outputData.push_back(data);
		return AIController::Behavior::MOVE_FORWARD;
	}
	else if (dis < 0.5f)
	{
		data.outputChoiceMode = "backward";
		m_outputData.push_back(data);
		return AIController::Behavior::MOVE_BACKWARD;
	}
	data.outputChoiceMode = "none";
	m_outputData.push_back(data);
	return AIController::Behavior::NONE;
}

void NeuralNetworkManager::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();

	debugFont->print(10, 190, L"error = %f%", m_error * 100);
	debugFont->draw();

	debugFont->print(700, 220, L"dis = %f", m_p);
	debugFont->draw();
	debugFont->print(700, 250, L"dis = %f", m_p / 18.0f);
	debugFont->draw();
	if (m_isDirectLeft) 
	{
		debugFont->print(700, 280, L"left = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(700, 280, L"left = false");
		debugFont->draw();
	}

	if (m_isDirectRight)
	{
		debugFont->print(700, 310, L"right = true");
		debugFont->draw();
	}
	else
	{
		debugFont->print(700, 310, L"right = false");
		debugFont->draw();
	}

	if (m_character->GetEnemySightContact())
	{
		float a = m_character->GetEnemySightContact();
		debugFont->print(700, 340, L"shoot = true");
		debugFont->draw();
	}
	else
	{
		float a = m_character->GetEnemySightContact();
		debugFont->print(700, 340, L"shoot = false");
		debugFont->draw();
	}
}

/// <summary>
/// 左右判定
/// </summary>
/// <param name="character"></param>
/// <param name="enemy"></param>
void NeuralNetworkManager::SearchDirection(Character* character, Character* enemy)
{
	Vector3 u;
	m_isDirectLeft = false;
	m_isDirectRight = false;

	DirectX::SimpleMath::Vector3 cv = Rotate(character->GetRadiansY(), DirectX::SimpleMath::Vector3::Forward);
	DirectX::SimpleMath::Vector3 rv = enemy->GetPosition() - character->GetPosition();
	rv.Normalize();
	DirectX::SimpleMath::Vector3 n = cv.Cross(rv);

	if (n.y > 0.1f)
		m_isDirectLeft = true;
	else if (n.y < -0.1f)
		m_isDirectRight = true;
}

/// <summary>
/// 
/// </summary>
/// <param name="angle"></param>
/// <param name="u"></param>
/// <returns></returns>
Vector3 NeuralNetworkManager::Rotate(float angle, Vector3 u)
{
	float	x, z;

	x = u.x * cos(angle) + u.z * sin(angle);
	z = -u.x * sin(angle) + u.z * cos(angle);

	return Vector3(x, 0, z);
}

/// <summary>
/// 入力と出力の値を外部に出力
/// </summary>
/// <param name="fname">出力するためのファイル</param>
void NeuralNetworkManager::OutputDataFile(char* fname)
{
	FILE* f;

	errno_t error;
	error = fopen_s(&f, fname, "w");

	fprintf(f, "--------------------------------------------------------------------------------------\n");
	fprintf(f, "IN Distance, Left, Right, Shoot, Hp,  OUT Distance, Left, Right, Shoot ,ChoiceMode \n");
	fprintf(f, "--------------------------------------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %s, %f%\n",output.inputDis,
			output.inputLeft, output.inputRight, output.inputShoot, output.inputHp,
			output.outputDis,output.outputLeft, output.outputRight,output.outputShoot,output.outputChoiceMode,m_error*100);
	}
	fclose(f);
}



