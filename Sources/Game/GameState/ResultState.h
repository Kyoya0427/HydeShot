//======================================================
// File Name	: ResultState.h
// Summary	: ���U���g�X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"
#include <SpriteBatch.h>
#include <SimpleMath.h>	
#include <Keyboard.h>

class ResultState :public IGameState
{
public:
	ResultState();

public:
	virtual ~ResultState();

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
	float m_count;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	DirectX::SimpleMath::Vector2                     m_pos;
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;


};

