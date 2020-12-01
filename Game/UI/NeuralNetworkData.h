//======================================================
// File Name	: NeuralNetworkData.h
// Summary		: ニューラルネットワーク情報
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class NeuralNetworkManager;

class NeuralNetworkData :public GameObject
{
public:
	//コンストラクタ
	NeuralNetworkData();
	//デストラクタ
	~NeuralNetworkData();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	//ニューラルネットワークのデータを取得
	void SetNeuralNetwork(NeuralNetworkManager* neuralNetwork) { m_neuralNetwork = neuralNetwork; }

private:
	//ニューラルネットワークマネージャー
	NeuralNetworkManager* m_neuralNetwork;

};