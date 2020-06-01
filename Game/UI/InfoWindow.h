#pragma once

#include <DirectXTK\SpriteBatch.h>

#include <Game\GameObject\GameObject.h>

#include <Game\UI\Blink.h>
#include <Game\UI\Letter.h>





class InfoWindow :public GameObject
{
public:
	//��ʃT�C�Y
	static constexpr int SCREEN_W = 1280 - 960;
	static constexpr int SCREEN_H = 720;
	
	//�P�O���b�g
	static constexpr int GRIT_SIZE = 24;
public:
	//�R���X�g���N�^
	InfoWindow();
	~InfoWindow();

	void Initialize();
	 void Update(const DX::StepTimer & timer) override;
	 void Render() override;
	 void HitContact(GameObject* object) override;

private:
	//�e�N�X�`���[�n���h���i�w�i�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bg01Texture;

};