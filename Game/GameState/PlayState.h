//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


#include "IGameState.h"

class GameWindow;
class InfoWindow;
class ObjectManager;

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

public: 
	//�|�[�Y��ʂɍs������
	void ChangePauseState();

private:
	// �Q�[����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                          m_viewportGame;
	// ����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                          m_viewportInfo;
	// ���E�B���h�E
	std::unique_ptr<InfoWindow>             m_infoWindow;
	//�Q�[���E�B���h�E
	std::unique_ptr<GameWindow>				m_gameWindow;
	// �Q�[���I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager>          m_objectManager;
};

