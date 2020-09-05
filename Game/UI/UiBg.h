//======================================================
// File Name	: UiBg.h
// Summary		: �w�i
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>

#include <Game/GameObject/GameObject.h>

class GameWindow;

class UiBg : public GameObject
{
public:
	// �R���X�g���N�^
	UiBg();
	//�f�X�g���N�^
	~UiBg();

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
	//�e�N�X�`���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>            m_spriteBatch;
};