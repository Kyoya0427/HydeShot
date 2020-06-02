//======================================================
// File Name	 : TitleState.h
// Summary	 : �^�C�g���X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\GameState\IGameState.h>


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
	void Render() override;
	//�I��
	void Finalize() override;



private:
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;


};

