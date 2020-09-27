//======================================================
// File Name	: SelectBg.h
// Summary		: �^�C�g���摜
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

class SelectBg : public GameObject
{
public:
	// �R���X�g���N�^
	SelectBg();
	//�f�X�g���N�^
	~SelectBg();

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