//======================================================
// File Name	: InfoWindow.h
// Summary		: ���E�B���h�E
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\SpriteBatch.h>

#include <Game\GameObject\GameObject.h>

class NeuralNetworkData;
class UiBg;
class SelectStateUi;
class HpUi;

class InfoWindow :public GameObject
{
public:
	//��ʃT�C�Y
	static constexpr int SCREEN_W = 1280 - 960;
	static constexpr int SCREEN_H = 720;
	
public:
	//�R���X�g���N�^
	InfoWindow();
	//�f�X�g���N�^
	~InfoWindow();

public:
	//������
	void Initialize();
	//�X�V
	void Update(const DX::StepTimer & timer) override;
	//�`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	//�e�N�X�`���[�n���h���i�w�i�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bg01Texture;
	//�j���[�����l�b�g���[�N�̃f�[�^
	std::unique_ptr<NeuralNetworkData>				 m_neuralNetworkData;
	//UI�w�i
	std::unique_ptr<UiBg>							 m_uiBg;
	//�I�������X�e�C�g
	SelectStateUi*									 m_selectState;
	//�L�����N�^�[��Hp
	HpUi*			                                 m_character;
};