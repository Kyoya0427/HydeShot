//======================================================
// File Name	: GameObject.h
// Summary		: �Q�[���I�u�W�F�N�g
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>

class GameObject
{
public:
	//�I�u�W�F�N�g�̎��
	enum class ObjectTag
	{
		None,
		Player,
		Enemy1,
		Enemy2,
		Bullet,
		Wall,
		Flag_01,
		Flag_02,
		Sight01,
		Sight02,


		NUM
	};

public:
	//�R���X�g���N�^
	GameObject(const ObjectTag tag = ObjectTag::None);

	//�f�X�g���N�^
	virtual ~GameObject();

public:
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;
	//�`��
	virtual void Render() = 0;
	//�����������Ƃ̏���
	virtual void OnCollision(GameObject* object) = 0;

public:
	// ����
	void Invalidate();
	//�L��
	bool IsValid() const;
	// ����
	bool IsInvalid() const;
	//�^�O���擾
	const ObjectTag GetTag() const;
	//���W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	//���x���擾
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	//��]�ʂ��擾
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	//�T�C�Y���擾
	const DirectX::SimpleMath::Vector3& GetScale() const;
	//�F��o�^
	DirectX::SimpleMath::Color GetColor();
	//�`�揇���擾
	const int GetDrawPrio() const;
	//�����蔻��̋��̔��a
	float GetRadius();
	//�e���������I�u�W�F�N�g�̃^�O���擾
	ObjectTag GetCharaTag();

public:
	//�^�O����o�^
	void SetTag(const ObjectTag tag);
	//���W��o�^
	void SetPosition(DirectX::SimpleMath::Vector3 position);
	//���x��o�^
	void SetVelocity(DirectX::SimpleMath::Vector3 velocity);
	//��]�ʂ�o�^
	void SetRotation(DirectX::SimpleMath::Vector3 rotation);
	//�T�C�Y��o�^
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	//�F��o�^
	void SetColor(DirectX::SimpleMath::Color color);
	//�`�揇��o�^
	void SetDrawPrio(int prio);
	//�e���������I�u�W�F�N�g�̃^�O��ݒ�
	void SetCharaTag(ObjectTag tag);
	//��\���ɂ���
	static void Destroy(GameObject* object);
	
private:
	//true�L��
	bool m_isValid;
	// �`�揇���Ǘ��p(�������قǎ�O�ɕ`�悳���j
	int m_drawPrio;
	
	
protected:
	//���W
	DirectX::SimpleMath::Vector3    m_position;
	//�x���V�e�B�[
	DirectX::SimpleMath::Vector3    m_velocity;
	//��]
	DirectX::SimpleMath::Vector3    m_rotation;
	//�T�C�Y
	DirectX::SimpleMath::Vector3    m_scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix     m_world;
	//�I�u�W�F�N�g�J���[
	DirectX::SimpleMath::Color      m_color;
	//�X�e�[�W��̈ʒu
	int m_x, m_y;
	//���a
	float  m_radius;
	//�I�u�W�F�N�g�^�O��
	ObjectTag m_tag;
	//�e���������I�u�W�F�N�g�̃^�O��
	ObjectTag           m_charaTag;
};
