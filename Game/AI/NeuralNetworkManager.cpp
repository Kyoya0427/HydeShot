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
#include <Game/Common/GameContext.h>

#include <Game/AI/NeuralNetwork.h>

#include <Game/CharaState/CharaStateID.h>

#include <Game/GameObject/Character.h>

#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="chara">ステイト操作するキャラクター</param>
/// <param name="enemy">敵キャラクター</param>
NeuralNetworkManager::NeuralNetworkManager(Character* character, Character* enemy)
	: m_isDirectionLeft()
	, m_isDirectionRight()
	, m_character(character)
	, m_enemy(enemy)
{
	m_neuralNetwork = std::make_unique<NeuralNetwork>();
	InitializeTraining(L"Resources//CSV//test6.csv");
	InitializeNeuralNetwork();
	m_error = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
NeuralNetworkManager::~NeuralNetworkManager()
{
	OutputDataFile("Resources//CSV//OutputData.csv");
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
	// ニューラルネットワークを初期化する(入力層:6、隠れ層:20、出力層:5)
	m_neuralNetwork->Initialize(6, 20, 5);

	// 学習率を設定する
	// Setup learning rate
	m_neuralNetwork->SetLearningRate(0.2);

	// モメンタムを設定する
	// Setup momentum
	m_neuralNetwork->SetMomentum(true, 0.9);

	float	error = 1.0;
	int		count = 0;    
	// 誤差逆伝播する(Back propagate)
	while (error > 0.01 && count < 1000)
	{
		error = 0.0;
		count++;
		for (int i = 0; i < MAX_DATA_H; i++)
		{
			//入力値
			//距離
			m_neuralNetwork->SetInput(0, m_training[i][0]);			
			//左判定
			m_neuralNetwork->SetInput(1, m_training[i][1]);			
			//右判定
			m_neuralNetwork->SetInput(2, m_training[i][2]);			
			//壁
			m_neuralNetwork->SetInput(3, m_training[i][3]);		
			//打つ
			m_neuralNetwork->SetInput(4, m_training[i][4]);			
			
			//出力値
			//距離
			m_neuralNetwork->SetDesiredOutput(0, m_training[i][5]);
			//左判定
			m_neuralNetwork->SetDesiredOutput(1, m_training[i][6]);
			//右判定
			m_neuralNetwork->SetDesiredOutput(2, m_training[i][7]);
			//壁
			m_neuralNetwork->SetDesiredOutput(3, m_training[i][8]);
			//打つ
			m_neuralNetwork->SetDesiredOutput(4, m_training[i][9]);

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
CharaStateID NeuralNetworkManager::BehaviorSelection()
{
	//距離計算
	float distance = Vector3::Distance(m_character->GetPosition(), m_enemy->GetPosition());
	m_distance     = distance;
	//左右判定
	SearchDirection(m_character, m_enemy);
	//距離
	m_neuralNetwork->SetInput(0, distance / 16.0f);
	//左判定
	m_neuralNetwork->SetInput(1, static_cast<float>(m_isDirectionLeft));
	//右判定
	m_neuralNetwork->SetInput(2, static_cast<float>(m_isDirectionRight));
	//目の前に壁がある
	m_neuralNetwork->SetInput(3, static_cast<float>(m_character->GetWallDiscovery()));
	//敵を撃てるか判定
	m_neuralNetwork->SetInput(4, static_cast<float>(m_character->GetEnemySightContact()));
	//計算開始
	m_neuralNetwork->FeedForward();

	//外部にデータ出力する為に保管
	m_data = {};

	m_data.inputDis        = distance / 16.0f;
	m_data.inputLeft       = static_cast<float>(m_isDirectionLeft);
	m_data.inputRight      = static_cast<float>(m_isDirectionRight);
	m_data.inputWall       = static_cast<float>(m_character->GetWallDiscovery());
	m_data.inputShoot      = static_cast<float>(m_character->GetEnemySightContact());

	m_data.outputDis       = m_neuralNetwork->GetOutput(0);
	m_data.outputLeft      = m_neuralNetwork->GetOutput(1);
	m_data.outputRight     = m_neuralNetwork->GetOutput(2);
	m_data.outputWall      = m_neuralNetwork->GetOutput(3);
	m_data.outputShoot     = m_neuralNetwork->GetOutput(4);

	//出力データから行動を選択
	float dis   = m_neuralNetwork->GetOutput(0);
	float wall  = m_neuralNetwork->GetOutput(3);
	float shot  = m_neuralNetwork->GetOutput(4);

	if (shot >= 0.5f)
	{
		m_data.outputChoiceMode = "ATTACK";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"ATTACK");
		return	CharaStateID::ATTACK;
	}
	else if (wall >= 0.8)
	{
		m_data.outputChoiceMode = "WALLAVOID";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"WALLAVOID");
		return	CharaStateID::WALLAVOID;
	}
	else if (dis > 0.001f)
	{
		m_data.outputChoiceMode = "SEARCH";
		m_outputData.push_back(m_data);
		GameContext::Get<SelectStateUi>()->SetSelectMode(L"SEARCH");
		return CharaStateID::SEARCH;
	}

	m_data.outputChoiceMode = "none";
	m_outputData.push_back(m_data);
	return CharaStateID::NONE;
}

/// <summary>
/// 左右判定
/// </summary>
/// <param name="character">自機</param>
/// <param name="enemy">敵</param>
void NeuralNetworkManager::SearchDirection(Character* character, Character* enemy)
{
	Vector3 u;
	//フラグを初期化
	m_isDirectionLeft = false;
	m_isDirectionRight = false;

	//左右判定計算
	Vector3 cv = Rotate(character->GetRadiansY(), Vector3::Forward);
	DirectX::SimpleMath::Vector3 rv = enemy->GetPosition() - character->GetPosition();
	rv.Normalize();
	DirectX::SimpleMath::Vector3 n = cv.Cross(rv);

	//適したフラグtrue
	if (n.y > 0.1f)
		m_isDirectionLeft = true;
	else if (n.y < -0.1f)
		m_isDirectionRight = true;
}

/// <summary>
/// 内積計算
/// </summary>
/// <param name="angle">ラジアン</param>
/// <param name="u">方向</param>
/// <returns></returns>
Vector3 NeuralNetworkManager::Rotate(float angle, const Vector3& u)
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

	fprintf(f, "-------------------------------------------------------------------------------------------------------\n");
	fprintf(f, "IN Distance, Left, Right, Wall, Shoot, Hp,  OUT Distance, Left, Right, Wall, Shoot ,ChoiceMode, Error  \n");
	fprintf(f, "-------------------------------------------------------------------------------------------------------\n");
	fprintf(f, "\n");
	
	for (auto& output : m_outputData)
	{
		fprintf(f, "%2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %2f, %s, %f%%  \n"
			,output.inputDis, output.inputLeft, output.inputRight, output.inputWall,output.inputShoot
			,output.outputDis, output.outputLeft, output.outputRight, output.outputWall, output.outputShoot
			,output.outputChoiceMode, m_error*100);
	}
	fclose(f);
}