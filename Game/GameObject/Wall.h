//======================================================
// File Name	: Wall.h
// Summary		: �ǃN���X
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/Collider/BoxCollider.h>

#include <Game/GameObject/GameObject.h>

class Stage;

class Wall : public GameObject
{
public:
	// �R���X�g���N�^
	Wall(const ObjectTag tag);
	// �f�X�g���N�^
	~Wall();

public:
	// �������֐�
	void Initialize(int x, int y);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

public:
	//�����蔻��̃T�C�Y���擾
	const DirectX::SimpleMath::Vector3& GetCollSize() const { return m_collSize; }
	// ���f���ݒ�֐�
	void SetModel(DirectX::Model* model)                    { m_model = model; }

private:
	//�e�N�X�`���[�n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model*                                     m_model;
	//�����蔻��I�u�W�F�N�g
	std::unique_ptr<DirectX::GeometricPrimitive>        m_boxCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>                        m_collider;
	//�����蔻��̃T�C�Y
	DirectX::SimpleMath::Vector3                        m_collSize;

};
