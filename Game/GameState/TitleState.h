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
	DirectX::Keyboard::KeyboardStateTracker          m_keyTracker;

	std::unique_ptr<TitleBg>                        m_titleBg;

	std::unique_ptr<Button>							m_playButton;

	std::unique_ptr<Button>							m_exitButton;

	SelectButtton                                   m_selectButton;

	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectTexture;
};