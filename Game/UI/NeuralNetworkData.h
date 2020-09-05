//======================================================
// File Name	: NeuralNetworkData.h
// Summary		: ニューラルネットワーク情報
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class NeuralNetworkData :public GameObject
{
public:
	//コンストラクタ
	NeuralNetworkData();
	~NeuralNetworkData();

public:
	void Initialize();
	void Update(const DX::StepTimer& timer) override;
	void Render() override;
	void OnCollision(GameObject* object) override;

private:


};