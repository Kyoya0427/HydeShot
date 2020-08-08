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
	void Initialize(const DirectX::SimpleMath::Vector2& pos);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

public:
	//�O�i
	void Forward(const float speed)   { m_velocity.z = -speed; }
	//��i
	void Backward(const float speed)  { m_velocity.z = speed;  }
	//���ɐi��
	void Leftward (const float speed) { m_velocity.x = -speed; }
	//�E�ɐi��
	void Rightward(const float speed) { m_velocity.x = speed;  }
	//���ɐ���
	void LeftTurn (const float speed) { m_rotation.y += speed; }
	//�E�ɐ���
	void RightTurn(const float speed) { m_rotation.y -= speed; }
	//���C
	void Shoot();

public:
	//hp���擾
	const int  GetHp() const                           { return m_hp; }
	//�ǂɐڐG���Ă邩���擾
	const bool GetWallContact() const                  { return m_isWallContact; }
	//�ǂɃZ���T�[���ڐG���Ă邩���擾
	const bool GetWallSightContact() const             { return m_isWallSightContact; }
	//�G�ɃZ���T�[���ڐG���Ă��邩���擾
	const bool GetEnemySightContact() const            { return m_isEnemySightContact; }
	//���݂̃X�e�[�g���擾
	const CharaStateID& GetCharaState() const          { return m_state; }
	//�ړ������ǃZ���T�[���擾
	WallApproach* GetWallApproachVel() const           { return m_wallApproachVel.get(); }
	//�ǔ������擾
	const bool GetWallDiscovery() const                { return m_isWallDiscovery; }
	
public:	
	//�ǔ����ݒ�
	void SetWallDiscovery(const bool wallFlont)       { m_isWallDiscovery = wallFlont; }
	//�ǂɃZ���T�[���ڐG���Ă邩�ݒ�
	void SetWallSightContact(const bool contact)      { m_isWallSightContact = contact; }
	//�G�ɃZ���T�[���ڐG���Ă��邩�ݒ�
	void SetEnemySightContact(const bool contact)     { m_isEnemySightContact = contact; }
	//���݂̃X�e�[�g��ݒ�
	void SetCharaState(const CharaStateID& state)     { m_state = state; }

public:
	//�ő�HP
	static const int  MAX_HP;

private:
	//���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	//�����蔻�胂�f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphereCollider;
	//�e���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_bulletModel;
	//�˒�
	std::unique_ptr<Sight>                       m_sight;
	//�ǂɐڋ߂��Ă��邩(�O��)
	std::unique_ptr<WallApproach>                m_wallApproach;
	//�ǂɐڋ߂��Ă��邩(�ړ�����)
	std::unique_ptr<WallApproach>                m_wallApproachVel;
	//�����蔻��
	std::unique_ptr<SphereCollider>              m_collider;
	//���݂̃X�e�[�g
	CharaStateID								 m_state;
	//�P�t���[���O�̍��W
	DirectX::SimpleMath::Vector3                 m_previousPos;
	//�ǂɃZ���T�[���ڐG���Ă邩
	bool                                         m_isWallSightContact;
	//�ǂɐڐG���Ă邩
	bool										 m_isWallContact;
	//�G�ɃZ���T�[���ڐG���Ă��邩
	bool                                         m_isEnemySightContact;
	//�ǔ���
	bool										 m_isWallDiscovery;
	//HP
	int                                          m_hp;
};