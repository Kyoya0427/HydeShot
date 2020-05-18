//======================================================
// File Name	: Camera.cpp
// Summary	: カメラ
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Camera.h"

#include <Game\GameState\PlayState.h>
/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	: m_eye()
	, m_projection()
	, m_target()
	, m_view()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize()
{
	//視点設定
	m_eye    = DirectX::SimpleMath::Vector3(7.0f, 15.5f, 16.0f);
	//注視点設定
	m_target = DirectX::SimpleMath::Vector3(7.0f, 0, 8.5f);
	//射影行列設定
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(45.0f),
		PlayState::SCREEN_W / static_cast<float>(PlayState::SCREEN_H),
		0.1f,
		200.0f);

	//カメラupを作成
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	
	// ビュー行列
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}
