//======================================================
// File Name	: TitleState.h
// Summary		: �^�C�g���X�e�C�g
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game\GameState\IGameState.h>

class TitleBg;
class Button;

class TitleState :public IGameState
{
	enum class SelectButtton
	{
		Play,
		Exit
	};
public:
	//�R���X�g���N�^
	TitleState();
	//�f�X�g���N�^
	 ~TitleState();

public:
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;
	//�I��
	void Finalize() override;

private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//�^�C�g���̔w�i
	std::unique_ptr<TitleBg>                            m_titleBg;
	//�v���C�{�^��
	std::unique_ptr<Button>							    m_playButton;
	//�C�O�W�b�g�{�^��
	std::unique_ptr<Button>							    m_exitButton;
	//���݂̃Z���N�g�{�^��
	SelectButtton                                       m_selectButton;
	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;
};