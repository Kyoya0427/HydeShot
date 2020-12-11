//======================================================
// File Name	: GameObject.h
// Summary		: �Q�[���I�u�W�F�N�g
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <string>

#include <DirectXTK/SimpleMath.h>

#include <Game/Common/StepTimer.h>

#include <Game/Collider/RaycastHit.h>


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
		Sight01,
		Sight02,
		WallApproach,
		
		NUM
	};

public:
	//�R���X�g���N�^
	GameObject(const ObjectTag& tag = ObjectTag::None);
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

public:
	//�^�O���擾
	const ObjectTag GetTag() const                          { return m_tag; }
	//���W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() const { return m_position; }
	//���x���擾
	const DirectX::SimpleMath::Vector3& GetVelocity() const { return m_velocity; }
	//��]�ʂ��擾
	const DirectX::SimpleMath::Vector3& GetRotation() const { return m_rotation; }
	//�T�C�Y���擾
	const DirectX::SimpleMath::Vector3& GetScale() const    { return m_scale; }
	//���[���h���W���擾
	const DirectX::SimpleMath::Matrix& GetWorld() const     { return m_world; }
	//�F���擾
	const DirectX::SimpleMath::Color& GetColor() const      { return m_color; }
	//�`�揇���擾
	const int GetDrawPrio() const							{ return m_drawPrio; }
	//�e���������I�u�W�F�N�g�̃^�O���擾
	ObjectTag GetCharaTag() const                           { return m_charaTag; }
	//���a���擾
	float GetRadius() const                                 { return m_radius; }
public:
	//�^�O����ݒ�
	void SetTag(const ObjectTag& tag)                              { m_tag = tag; }
	//���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	//���x��ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//���xX��ݒ�
	void SetVelocityX(const float x)                               { m_velocity.x = x; }
	//���xY��ݒ�
	void SetVelocityY(const float y)                               { m_velocity.y = y; }
	//���xZ��ݒ�
	void SetVelocityZ(const float z)                               { m_velocity.z = z; }
	//��]�ʂ�ݒ�
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	//��]��X��ݒ�
	void SetRotationX(const float x)                               { m_rotation.x = x; }
	//��]��Y��ݒ�
	void SetRotationY(const float y)                               { m_rotation.y = y; }
	//��]��Z��ݒ�
	void SetRotationZ(const float z)                               { m_rotation.z = z; }
	//�T�C�Y��ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale)       { m_scale = scale; }
	//���[���h���W��ݒ�
	void SetWorld(const DirectX::SimpleMath::Matrix& world)        { m_world = world; }
	//�F��ݒ�
	void SetColor(const DirectX::SimpleMath::Color color)          { m_color = color; }
	//�`�揇��ݒ�
	void SetDrawPrio(int drawPrio)                                 { m_drawPrio = drawPrio; }
	//�e���������I�u�W�F�N�g�̃^�O��ݒ�
	void SetCharaTag(const ObjectTag& tag)                         { m_charaTag = tag; }
	//���a��ݒ�
	void SetRadius(float radius)                                   { m_radius = radius; }

public:
	//��\���ɂ���
	static void Destroy(GameObject* object);
	
private:
	//true�L��
	bool                            m_isValid;
	// �`�揇���Ǘ��p(�������قǎ�O�ɕ`�悳���j
	int                             m_drawPrio;
	
private:
	//�I�u�W�F�N�g�^�O��
	ObjectTag                       m_tag;
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
	//���a
	float                           m_radius;
	//�e���������I�u�W�F�N�g�̃^�O��
	ObjectTag                       m_charaTag;

};

/// <summary>
/// ��]�ʂ�ݒ�
/// </summary>
/// <param name="rotation">��]��</param>
inline void GameObject::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
{
	float radians = DirectX::XMConvertToRadians(DirectX::XMConvertToDegrees(rotation.y));
	
	if (radians > DirectX::XM_2PI)
		radians = 0.0f;
	if (radians < -DirectX::XM_2PI)
		radians = 0.0f;

	if (m_rotation.y < 0.0f)
		radians = DirectX::XM_2PI + radians;

	m_rotation = DirectX::SimpleMath::Vector3(rotation.x, radians, rotation.z);
}