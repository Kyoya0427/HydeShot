//======================================================
// File Name	 : PlayState.h
// Summary		 : �v���C�X�e�C�g
// Date			 : 2020/5/12
// Author		 : Kyoya  Sakamoto
//======================================================
#pragma once

#include <list>

#include <Game\GameState\IGameState.h>

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

class PlayState : public IGameState
{
public:
	PlayState();
	 ~PlayState();

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
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;
	static bool		 m_isDebug;

private:
	// �Q�[����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                              m_viewportGame;
	// ����ʂ̃r���[�|�[�g
	D3D11_VIEWPORT                              m_viewportInfo;
	// ���E�B���h�E
	std::unique_ptr<InfoWindow>                 m_infoWindow;
	//Camera
	std::unique_ptr <Camera>                    m_camera;
	//�o�b�N�O���E���h
	std::unique_ptr<Bg>                         m_bg;
	//�X�e�[�W
	std::unique_ptr<Stage>					    m_stage;
	//�G�l�~�[
	std::unique_ptr<Character>                  m_enemy[2];
	//�v���C���[
	std::unique_ptr<Character>                  m_player;
	//�G�l�~�[�R���g���[���[
	std::unique_ptr<AIController>               m_aiController[2];
	//�v���C���[�R���g���[���[
	std::unique_ptr<PlayerController>           m_playerControll;
	// �Q�[���I�u�W�F�N�g�}�l�[�W���[
	std::unique_ptr<ObjectManager>              m_objectManager;
	//�����蔻��}�l�[�W���[
	std::unique_ptr<CollisionManager>           m_collisionManager;
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker		m_keyTracker;

};

