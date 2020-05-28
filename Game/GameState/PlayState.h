//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <list>

#include <Game\Common\StepTimer.h>

class GameWindow;
class InfoWindow;
class ObjectManager;
class Camera;
class PlayerController;
class AIController;
class Stage;
class Bg;
class Character;
class Collision;
class ArtilleryShell;
class CollisionManager;

class PlayState 
{
public:
	PlayState();
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
	std::unique_ptr<Character>              m_player;
	//�v���C�C���[�R���g���[���[
	std::unique_ptr<PlayerController>       m_playerController;
	//�G�l�~�[
	std::unique_ptr<Character>              m_enemy;
	//�G�l�~�[�R���g���[���[
	std::unique_ptr<AIController>           m_aiController;
	// �Q�[���I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager>          m_objectManager;
	//�����蔻��}�l�[�W���[
	std::unique_ptr<CollisionManager>       m_collisionManager;
};

