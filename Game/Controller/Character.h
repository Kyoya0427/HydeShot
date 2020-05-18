//======================================================
// File Name	: CharacterController.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class Character : public IGameObject
{
public:
	//�R���X�g���N
	Character(const ObjectTag tag = ObjectTag::None);
	//�f�X�g���N�^
	~Character();

public:
	//�O�i
	void Forward  (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//��i
	void Backward (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//���ɐi��
	void Leftward (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//�E�ɐi��
	void Rightward(DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//���ɐ���
	void LeftTurn (DirectX::SimpleMath::Vector3& rot, float speed);
	//�E�ɐ���
	void RightTurn(DirectX::SimpleMath::Vector3& rot, float speed);
};