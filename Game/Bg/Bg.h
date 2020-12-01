//======================================================
// File Name	: Bg.h
// Summary		: �Q�[���w�i
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/Model.h>

#include <Game/GameObject/GameObject.h>

class GameWindow;

class Bg : public GameObject
{
public:
	//�R���X�g���N�^
	Bg();
	//�f�X�g���N�^
	~Bg();

public:
	//�������֐�
	void Initialize();
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��֐�
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

private:
	//���f���f�[�^�ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_model;

};