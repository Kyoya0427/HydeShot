//======================================================
// File Name	: MyGame.h
// Summary	: �}�C�Q�[��
//======================================================
#pragma once

#include <Game\Common\StepTimer.h>

class GameStateManager;

class MyGame
{
public:
	//�R���X�g���N�^
	MyGame();
	//�f�X�g���N�^
	~MyGame();

public:
	//������
	void Initialize();
	//�X�V
	void Update(const DX::StepTimer& timer);
	//�`��
	void Render(const DX::StepTimer& timer);
	//�I��
	void Finalize();

private:

	//�X�e�C�g�}�l�W���[
	std::unique_ptr<GameStateManager>          m_stateManager;
};