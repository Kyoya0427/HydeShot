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
	static bool		 m_isPlayerWin;

private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	//���U���g�w�i
	std::unique_ptr<ResultBg>                        m_resultBg;
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushTexture;
	//�e�N�X�`���[���W
	DirectX::SimpleMath::Vector2                     m_pushPos;
	//�u�����N
	std::unique_ptr<Blink>                           m_blink;
	//�u�����N���g�p���邩
	bool                                             m_isBlink;

};