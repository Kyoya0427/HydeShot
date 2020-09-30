//======================================================
// File Name	 : SelectState.h
// Summary		 : �Z���N�g�X�e�C�g

// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/GameState/IGameState.h>

#include <Game/Bg/SelectBg.h>

#include <Game/UI/Button.h>
#include <Game/UI/OptionList.h>

#include <Game/GameObject/SelectMode.h>

class Blink;

class SelectState :public IGameState
{
public:
	enum class SelectCharacter
	{
		ENEMY,
		PLAYER,
		
		NUM
	};
public:
	//�R���X�g���N�^
	SelectState();
	//�f�X�g���N�^
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
	static SelectMode GetBlueMode()         { return m_blueMode; }
	static SelectMode GetRedMode()          { return m_redMode; }
	static SelectCharacter GetSelectChara() { return m_selectChara; }

public:
	//�L�����N�^�[
	static SelectMode                                   m_blueMode;
	//�ԃL�����N�^�[�̑I��
	static SelectCharacter								m_selectChara;
	//�ԃL�����N�^�[
	static SelectMode                                   m_redMode;

public:
	//�ԃL�����N�^�[���[�h�Z���N�g
	void ChangeRedMode()  { m_currentOption = m_redOption.get(); }
	//�L�����N�^�[���[�h�Z���N�g
	void ChangeBlueMode() { m_currentOption = m_blueOption.get(); }
	//�Ԃ̃��[�h���X�g�ɒǉ�
	void AddRedMode();
private:
	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_selectTexture;	
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_redTexture;	
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_blueTexture;
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_redCharaTexture;
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    m_blueCharaTexture;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>               m_spriteBatch;
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker             m_keyTracker;
	//�Z���N�g�̔w�i
	std::unique_ptr<SelectBg>                           m_selectBg;
	//���[�h��I��
	std::unique_ptr<OptionList>						    m_selectMode;
	//�ԃL�����N�^�[���[�h�Z���N�g
	std::unique_ptr<OptionList>							m_redOption;
	//�L�����N�^�[���[�h�Z���N�g
	std::unique_ptr<OptionList>							m_blueOption;
	//���쒆�̃��[�h���X�g
	OptionList*                                         m_currentOption;
	//���[�h��I�����Ă��邩
	bool												m_isSelectMode;
	//�u�����N
	std::unique_ptr<Blink>                              m_blink;
	//�Ԃ�I��
	bool                                                m_isRedSelect;
};