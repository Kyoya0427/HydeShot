//======================================================
// File Name	: Bg.h
// Summary		: �w�i
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK\Model.h>

#include <Game\GameObject\GameObject.h>

class GameWindow;

class Bg : public GameObject
{
public:
	// �R���X�g���N�^
	Bg();
	//�f�X�g���N�^
	~Bg();

public:
	// �������֐�
	void Initialize();
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	// �Q�[���E�C���h�E�ւ̃|�C���^
	GameWindow* m_gameWindow;
	// ���f���f�[�^�ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_model;
	// ��]�p
	float m_angle;
};