//======================================================
// File Name	: Character.h
// Summary		: �L�����N�^�[
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/GeometricPrimitive.h>

#include <Game/GameObject/GameObject.h>

#include <Game/Common/StepTimer.h>

#include <Game/Collider/SphereCollider.h>

#include <Game/CharaState/CharaStateID.h>

class Sight;
class WallApproach;

class Character : public GameObject
{
public:
	//�R���X�g���N
	Character(const ObjectTag tag = ObjectTag::None);
	//�f�X�g���N�^
	~Character();

public:
	// �������֐�
	void Initialize(DirectX::SimpleMath::Vector2& pos);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

public:
	//�O�i
	void Forward  (float speed);
	//��i
	void Backward (float speed);
	//���ɐi��
	void Leftward (float speed);
	//�E�ɐi��
	void Rightward(float speed);
	//���ɐ���
	void LeftTurn (float speed);
	//�E�ɐ���
	void RightTurn(float speed);
	//���C
	void Shoot();

public:
	//hp���擾
	int  GetHp();
	//�ǂɐڐG���Ă邩
	bool GetWallContact();
	//�ǂɃZ���T�[���ڐG���Ă邩
	bool GetWallSightContact();
	//�ǂɃZ���T�[���ڐG���Ă邩�ݒ�
	void SetWallSightContact(bool contact);
	//�G�ɃZ���T�[���ڐG���Ă��邩
	bool GetEnemySightContact();
	//�G�ɃZ���T�[���ڐG���Ă��邩�ݒ�
	void SetEnemySightContact(bool contact);
	
	void SetCharaState(CharaStateID state);

	CharaStateID GetCharaState();

	Sight* GetSight();

	WallApproach* GetWallApproachVel();

	bool GetWallFlont();
	void SetWallFlont(bool wallFlont);

public:
	//�ő�HP
	static const int  MAX_HP;

	

private:
	//���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	//�˒�
	std::unique_ptr<Sight>                       m_sight;
	//�ǂɐڋ߂��Ă��邩(�O��)
	std::unique_ptr<WallApproach>                m_wallApproach;
	//�ǂɐڋ߂��Ă��邩(�ړ�����)
	std::unique_ptr<WallApproach>                m_wallApproachVel;
	//�����蔻��
	std::unique_ptr<SphereCollider>              m_collider;
	
	CharaStateID								 m_state;
	//�P�t���[���O�̍��W
	DirectX::SimpleMath::Vector3                 m_previousPos;
	//�ǂɃZ���T�[���ڐG���Ă邩
	bool                                         m_wallSightContact;
	//�ǂɐڐG���Ă邩
	bool										 m_wallContact;
	//�G�ɃZ���T�[���ڐG���Ă��邩
	bool                                         m_enemySightContact;

	bool										 m_isWallflont;


	//HP
	int                                          m_hp;
};