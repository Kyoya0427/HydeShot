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
	: m_eye()
	, m_projection()
	, m_target()
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



