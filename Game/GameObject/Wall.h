//======================================================
// File Name	: Wall.h
// Summary		: �ǃN���X
// Date			: 2020/5/12
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

	void OnCollision(GameObject* object) override;
	// ���f���ݒ�֐�
	void SetModel(DirectX::Model* model);
	//�����蔻��̃T�C�Y���擾
	DirectX::SimpleMath::Vector3 GetCollSize();

private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models;
	//�����蔻��I�u�W�F�N�g
	std::unique_ptr<DirectX::GeometricPrimitive> m_boxCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>  m_collider;
	//�����蔻��̃T�C�Y
	DirectX::SimpleMath::Vector3  m_collSize;

};
