//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\Common\StepTimer.h>

class GameWindow;
class InfoWindow;
class ObjectManager;
class Camera;
class Player;
class Enemy;
class Stage;
class Bg;

class PlayState 
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	//������
	void Initialize();
	//�X�V
	void Update(const DX::StepTimer& timer);
	//�`��
	void Render(const DX::StepTimer& timer);
	//�I��
	void Finalize();

public: 
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;

private:
	// �Q�[����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                          m_viewportGame;
	// ����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                          m_viewportInfo;
	// ���E�B���h�E
	std::unique_ptr<InfoWindow>             m_infoWindow;
	//Camera
	std::unique_ptr <Camera>                m_camera;
	//�o�b�N�O���E���h
	std::unique_ptr<Bg>                     m_bg;
	//�X�e�[�W
	std::unique_ptr<Stage>					m_stage;
	//�v���C�C���[
	std::unique_ptr<Player>                 m_player;
	//�G�l�~�[
	std::unique_ptr<Enemy>                  m_enemy;
	// �Q�[���I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager>          m_objectManager;
};

