//======================================================
// File Name	 : SelectState.h
// Summary		 : �Z���N�g�X�e�C�g
// Date		     : 2020/5/12
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/GameState/IGameState.h>

#include <Game/Bg/SelectBg.h>

#include <Game/UI/Button.h>

#include <Game/GameObject/SelectMode.h>

class SelectState :public IGameState
{
public:
	enum class SelectCharacter
	{
		PLAYER,
		ENEMY,

		NUM
	};

	enum class Menu
	{
		BLUE,
		SELECT,
		RED
	};

public:
	SelectState();

public:
	~SelectState();

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
	SelectMode GetBlueMode()         { return m_blueMode; }
	SelectMode GetRedMode()          { return m_redMode; }
	SelectCharacter GetSelectChara() { return m_selectChara; }

private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//�Z���N�g�̔w�i
	std::unique_ptr<SelectBg>                           m_selectBg;
	//�L�����N�^�[���[�h�Z���N�g
	std::unique_ptr<Button>							    m_blueButton[4];
	//�L�����Z���N�g�{�^��
	std::unique_ptr<Button>							    m_charaSelectButton[static_cast<int>(SelectCharacter::NUM)];
	//�ԃL�����N�^�[���[�h�Z���N�g
	std::unique_ptr<Button>							    m_redButton[static_cast<int>(SelectMode::NUM)];
	//�L�����N�^�[
	SelectMode                                          m_blueMode;
	//�ԃL�����N�^�[�̑I��
	SelectCharacter										m_selectChara;
	//�ԃL�����N�^�[
	SelectMode                                          m_redMode;
	//�I�𒆂̃��j���[
	Menu                                                m_menu;
	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;
};