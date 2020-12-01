//======================================================
// File Name	: ResultBg.h
// Summary		: ���U���g�w�i
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

class GameWindow;

class ResultBg : public GameObject
{
public:
	// �R���X�g���N�^
	ResultBg();
	//�f�X�g���N�^
	~ResultBg();

public:
	// �������֐�
	void Initialize(const DirectX::SimpleMath::Vector3& pos);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	//�f�t�H���g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winTexture;
	//�Z���N�g�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_loseTexture;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;

};