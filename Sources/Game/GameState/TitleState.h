//======================================================
// File Name	 : TitleState.h
// Summary	 : �^�C�g���X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>	
#include <Keyboard.h>
#include <Game\UI\Blink.h>

class TitleState :public IGameState
{
public:
	TitleState();

public:
	virtual ~TitleState();

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

	void SelectPartsMode(bool flag);

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	DirectX::SimpleMath::Vector2                     m_pos;
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;
	DirectX::SimpleMath::Vector2                     m_pushPos;

	std::unique_ptr<Blink>                           m_blink;
	bool                                             m_blinkFlag;
};

