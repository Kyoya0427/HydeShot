//======================================================
// File Name	: Camera.cpp
// Summary	: ÉJÉÅÉâ
//======================================================
#include "Camera.h"

#include <Game\GameWindow\GameWindow.h>

Camera::Camera()
	: m_eye()
	, m_projection()
	, m_target()
	, m_view()
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	m_eye = DirectX::SimpleMath::Vector3(4.5f, 10.5f, 11.0f);
	m_target = DirectX::SimpleMath::Vector3(4.5f, 0, 5.5f);

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(45.0f),
		GameWindow::SCREEN_W / static_cast<float>(GameWindow::SCREEN_H),
		0.1f,
		200.0f);

	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}
