//======================================================
// File Name	: IGameObject.h
// Summary	: �Q�[���I�u�W�F�N�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>




class IGameObject
{
public:
	//�I�u�W�F�N�g�̎��
	enum ObjectTag
	{
		None,
		Player,
		Enemy
	};

public:
	//�R���X�g���N�^
	IGameObject(const ObjectTag tag = ObjectTag::None);

	//�f�X�g���N�^
	virtual ~IGameObject();

public:
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;
	//�`��
	virtual void Render(const DX::StepTimer& timer) = 0;
	//�����������Ƃ̏���
	virtual void OnCollision(IGameObject* object) = 0;

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
	//��]�ʂ��擾
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	//�T�C�Y���擾
	const DirectX::SimpleMath::Vector3& GetScale() const;
	//�`�揇���擾
	const int GetDrawPrio() const;
	//�^�O����o�^
	void SetTag(const ObjectTag tag);
	//���W��o�^
	void SetPosition(DirectX::SimpleMath::Vector3& position);
	//��]�ʂ�o�^
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	//�T�C�Y��o�^
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	//�`�揇��o�^
	void SetDrawPrio(int prio);
	//��\���ɂ���
	static void Destroy(IGameObject* object);

private:
	//true�L��
	bool m_isValid;
	// �`�揇���Ǘ��p(�������قǎ�O�ɕ`�悳���j
	int m_drawPrio;
	//�^�O
	ObjectTag m_tag;

	
protected:
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�x���V�e�B�[
	DirectX::SimpleMath::Vector3 m_velocity;
	//��]
	DirectX::SimpleMath::Vector3 m_rotation;
	//�T�C�Y
	DirectX::SimpleMath::Vector3 m_scale;
	//���[���h�s��
	DirectX::SimpleMath::Matrix     m_world;

	// �X�e�[�W��̈ʒu
	int m_x, m_y;
};




