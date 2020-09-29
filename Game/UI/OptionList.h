//======================================================
// File Name	 : OptionList.h
// Summary		 : �I�������X�g
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

class Button;

class OptionList
{
public:
	//�R���X�g���N�^
	OptionList();
	//�f�X�g���N�^
	~OptionList();

public:
	//�X�V
	void Update();
	//�`��
	void Render();
	//�ǉ�
	void Add(DirectX::SimpleMath::Vector2 pos, wchar_t* letter);
	
	void CurrentUp();
	void CurrentDown();

public:
	//���݂̑I�����擾
	int GetCurrent() { return m_current; }
	//�e�N�X�`���[��ݒ�
	void SetTexture(ID3D11ShaderResourceView* default, ID3D11ShaderResourceView* select);


private:
	//���݂̑I����
	int									   m_current;
	std::vector<std::unique_ptr<Button>>   m_button;
	//�f�t�H���g�e�N�X�`���[
	ID3D11ShaderResourceView*              m_defaultTexture;
	//�Z���N�g�e�N�X�`���[
	ID3D11ShaderResourceView*              m_selectTexture;
};
