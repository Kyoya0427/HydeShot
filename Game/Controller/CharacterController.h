//======================================================
// File Name	: CharacterController.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class CharacterController : public IGameObject
{
public:
	//�R���X�g���N
	CharacterController(const ObjectTag tag = ObjectTag::None);
	//�f�X�g���N�^
	~CharacterController();

public:
	//�O�i
	void Forward(float speed);
	//��i
	void Backward(float speed);
	//���ɐi��
	void Leftward(float speed);
	//�E�ɐi��
	void Rightward(float speed);
	//���ɐ���
	void LeftTurn(float speed);
	//�E�ɐ���
	void RightTurn(float speed);
};