//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <memory>

#include <Model.h>

#include "IGameState.h"

class CollisionManager;
class PlayerManager;
class TPSCamera;
class StageManager;

class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;
	//�I��
	void Finalize() override;

private:

	//�����蔻��}�l�[�W���[
	std::unique_ptr<CollisionManager>   m_collisionManager;
	//�X�e�[�W�}�l�[�W���[
	std::unique_ptr<StageManager>       m_stageManager;
	//�v���C���[�}�l�[�W���[
	std::unique_ptr<PlayerManager>      m_playerManager;
	//TPS�J����
	std::unique_ptr<TPSCamera>          m_tpsCamera;


};

