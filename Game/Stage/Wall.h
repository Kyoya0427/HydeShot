//======================================================
// File Name	: Wall.h
// Summary	: ���N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\Model.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Collider\BoxCollider.h>

#include <Game\GameObject\GameObject.h>

class Stage;

class Wall : public GameObject
{
private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models;

	//�����蔻��I�u�W�F�N�g
	std::unique_ptr<DirectX::GeometricPrimitive> m_boxCollider;
	//�����蔻��
	std::unique_ptr<BoxCollider>  m_collider;

	DirectX::SimpleMath::Vector3  m_collSize;
public:
	// �R���X�g���N�^
	Wall();

	// �������֐�
	void Initialize(int x, int y);

	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer & timer) override;

	void HitContact(GameObject* object) override;

	// ���f���ݒ�֐�
	void SetModel( DirectX::Model* model);

	DirectX::SimpleMath::Vector3 GetCollSize();

};
