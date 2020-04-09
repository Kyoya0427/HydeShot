//======================================================
// File Name	: ResultState.h
// Summary	: ���U���g�X�e�C�g
//======================================================
#pragma once

#include "IGameState.h"


class ResultState :public IGameState
{
public:
	ResultState();

public:
	virtual ~ResultState();

public:
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;
	//�I��
	void Finalize() override;
};

