//======================================================
// File Name	: Floor.h
// Summary		: ���N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\Model.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\GameObject\GameObject.h>

class Stage;

class Floor : public GameObject
{	
private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models;

public:
	// �R���X�g���N�^
	Floor();

public:
	// �������֐�
	void Initialize(int x, int y);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

	// ���f���ݒ�֐�
	void SetModel(DirectX::Model* model);

};
