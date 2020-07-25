//======================================================
// File Name	: IGameState.h
// Summary		: �Q�[���X�e�C�g�̊��N���X
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\Common\StepTimer.h>

class IGameState
{
public:
	IGameState() = default;

public:
	virtual ~IGameState() = default;

public:
	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;
	//�`��
	virtual void Render() = 0;
	//�I��
	virtual void Finalize() = 0;

};