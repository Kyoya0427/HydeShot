//======================================================
// File Name	: ResultState.h
// Summary		: ���U���g�X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SimpleMath.h>	
#include <DirectXTK\Keyboard.h>

#include <Game\GameState\IGameState.h>

#include <Game\UI\Blink.h>

class ResultBg;

class ResultState :public IGameState
{
public:
	//�R���X�g���N�^
	ResultState();
	//�f�X�g���N�^
	 ~ResultState();

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
	void SelectPartsMode(bool flag);

public:
	static bool		 m_isPlayerWin;


private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;

	std::unique_ptr<ResultBg>                        m_resultBg;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;
	DirectX::SimpleMath::Vector2                     m_pushPos;
	std::unique_ptr<Blink>                           m_blink;
	bool                                             m_blinkFlag;

};

