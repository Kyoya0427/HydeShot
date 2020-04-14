//======================================================
// File Name	: Bg.h
// Summary	: �w�i�N���X
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>
#include <DirectXTK\Model.h>

class GameWindow;

class Bg : public IGameObject
{
	// �Q�[���E�C���h�E�ւ̃|�C���^
	GameWindow* m_gameWindow;

	// ���f���f�[�^�ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_model;

	// ��]�p
	float m_angle;

public:
	// �R���X�g���N�^
	Bg();
	
	// �������֐�
	void Initialize();

	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer& timer) override;

	void OnCollision(IGameObject* object) override;
};