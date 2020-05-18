//======================================================
// File Name	: Camera.cpp
// Summary	: �J����
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Camera.h"

#include <Game\GameState\PlayState.h>
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
	m_eye    = DirectX::SimpleMath::Vector3(7.0f, 15.5f, 16.0f);
	//�����_�ݒ�
	m_target = DirectX::SimpleMath::Vector3(7.0f, 0, 8.5f);
	//�ˉe�s��ݒ�
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(45.0f),
		PlayState::SCREEN_W / static_cast<float>(PlayState::SCREEN_H),
		0.1f,
		200.0f);

	//�J����up���쐬
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	
	// �r���[�s��
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}
