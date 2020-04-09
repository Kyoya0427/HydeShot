//======================================================
// File Name	 : TitleState.h
// Summary	 : �^�C�g���X�e�C�g
//======================================================
#pragma once

#include "IGameState.h"


class TitleState :public IGameState
{
public:
	TitleState();

public:
	virtual ~TitleState();

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

