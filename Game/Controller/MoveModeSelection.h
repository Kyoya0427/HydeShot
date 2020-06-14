//======================================================
// File Name	: MoveModeSelection.h
// Summary		: ÉÇÅ[ÉhëIë
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/Controller/AIController.h>

class NeuralNetwork;

class MoveModeSelection
{
public:
	MoveModeSelection();
	~MoveModeSelection();

public:
	static const int MAX_DATA_H = 3920; 
	static const int MAX_DATA_W = 4; 

public:
	void InitializeTraining(wchar_t* fname);
	void InitializeNeuralNetwork();
	AIController::Behavior BehaviorSelection(float x, float y, int hp);
	void Render();
public: 

	std::vector<std::vector<double>> m_training;
	double                           m_error;
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
};

