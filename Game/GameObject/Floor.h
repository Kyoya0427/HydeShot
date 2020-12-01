//======================================================
// File Name	: Floor.h
// Summary		: ���N���X
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>
#include <DirectXTK/GeometricPrimitive.h>

#include <Game/GameObject/GameObject.h>

class Stage;

class Floor : public GameObject
{	
public:
	// �R���X�g���N�^
	Floor();

public:
	// �������֐�
	void Initialize(const int x, const int y);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

public:
	// ���f���ݒ�֐�
	void SetModel(DirectX::Model* model) { m_model = model; }

private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model*			m_model;

};
