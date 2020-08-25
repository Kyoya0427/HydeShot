//======================================================
// File Name	: Button.h
// Summary		: UI�{�^��
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Game/Common/StepTimer.h>

class Button
{
public:
	Button();
	~Button();

public:
	// �������֐�
	void Initialize(const DirectX::SimpleMath::Vector2& pos, wchar_t* letter);
	// �X�V
	void Update(const DX::StepTimer& timer);
	// �`��֐�
	void Render();
	//����������̏���
	

public:
	void SetSelect(const bool select) { m_isSelect = select; }
	void SetDefaultTexture(ID3D11ShaderResourceView* texture) { m_defaultTexture = texture; }
	void SetSelectTexture(ID3D11ShaderResourceView* texture)  { m_selectTexture = texture; }

private:
	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_selectTexture;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
	//�摜�I��p
	bool											 m_isSelect;
	//�{�^���̕���
	wchar_t*                                         m_letter;

	DirectX::SimpleMath::Vector2                     m_position;
};

