//======================================================
// File Name	: ResultState.h
// Summary		: ���U���g�X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SimpleMath.h>	
#include <DirectXTK\Keyboard.h>

#include <Game\GameState\IGameState.h>

class ResultState :public IGameState
{
public:
	ResultState();
	virtual ~ResultState();

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

