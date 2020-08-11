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
	//�R���X�g���N�^
	ResultState();
	//�f�X�g���N�^
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

public:
	static bool		 m_isPlayerWin;


private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;

};

