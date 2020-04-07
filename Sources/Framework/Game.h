//======================================================
// File Name	:Game.h
// Summary	: �Q�[��
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SpriteBatch.h>
#include <CommonStates.h>
#include <Keyboard.h>
#include <Mouse.h>

#include "DeviceResources.h"
#include "StepTimer.h"

class MyGame;

// �Q�[�����[�v��񋟂���Q�[���N���X
class Game : public DX::IDeviceNotify
{
public:
	//�R���X�g���N�^
    Game() noexcept(false);
	//�f�X�g���N�^
	~Game();
public:
    //������
    void Initialize(HWND window, int width, int height);

    //�Q�[�����[�v
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    //���b�Z�[�W
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    //�v���p�e�B
    void GetDefaultSize( int& width, int& height ) const;
	void ChangeFullscreen(BOOL flag);

private:
	//�X�V
    void Update(DX::StepTimer const& timer);
    //�`��
	void Render();
	//��ʂ��N���A����
    void Clear();
	//�f�o�C�X�𐶐�
    void CreateDeviceDependentResources();
	//�E�B���h�E
    void CreateWindowSizeDependentResources();

    //�f�o�C�X���\�[�V�[�Y
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;
	//�^�C�}�[
	DX::StepTimer                               m_timer;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>       m_spriteBatch;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	    m_state;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			    m_mouse;
	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>          m_keyboard;
	//�}�C�Q�[��
	std::unique_ptr<MyGame>                     m_myGame;
};