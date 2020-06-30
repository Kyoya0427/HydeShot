//======================================================
// File Name	: Camera.cpp
// Summary		: �J����
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Camera.h"

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
	: m_eye(0.0f, 0.0f, 0.0f)
	, m_projection()
	, m_target(0.0f, 0.0f, 0.0f)
	, m_view()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// ������
/// </summary>
void Camera::Initialize()
{
	//���_�ݒ�
	m_eye        = Vector3(7.2f, 16.0f, 16.0f);
	//�����_�ݒ�
	m_target     = Vector3(7.2f, 0, 8.5f);
	//�ˉe�s��ݒ�
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		PlayState::SCREEN_W / static_cast<float>(PlayState::SCREEN_H),
		0.1f,
		200.0f);
	//�J����up���쐬
	Vector3 up   = Vector3(0.0f, 1.0f, 0.0f);
	// �r���[�s��
	m_view       = Matrix::CreateLookAt(m_eye, m_target, up);
}

/// <summary>
/// �r���[�s��擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Camera::GetView()
{
	return m_view;
}

/// <summary>
/// ���_�擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Camera::Geteye()
{
	return m_eye;
}

/// <summary>
/// �����_�擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Camera::GetTarget()
{
	return m_target;
}

/// <summary>
/// �ˉe�s��擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Camera::GetProjection()
{
	return m_projection;
}


