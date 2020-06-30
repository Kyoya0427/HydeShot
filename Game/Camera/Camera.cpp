//======================================================
// File Name	: Camera.cpp
// Summary		: カメラ
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Camera.h"

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
	: m_eye(0.0f, 0.0f, 0.0f)
	, m_projection()
	, m_target(0.0f, 0.0f, 0.0f)
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
	m_eye        = Vector3(7.2f, 16.0f, 16.0f);
	//注視点設定
	m_target     = Vector3(7.2f, 0, 8.5f);
	//射影行列設定
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		PlayState::SCREEN_W / static_cast<float>(PlayState::SCREEN_H),
		0.1f,
		200.0f);
	//カメラupを作成
	Vector3 up   = Vector3(0.0f, 1.0f, 0.0f);
	// ビュー行列
	m_view       = Matrix::CreateLookAt(m_eye, m_target, up);
}

/// <summary>
/// ビュー行列取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Camera::GetView()
{
	return m_view;
}

/// <summary>
/// 視点取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Camera::Geteye()
{
	return m_eye;
}

/// <summary>
/// 注視点取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Camera::GetTarget()
{
	return m_target;
}

/// <summary>
/// 射影行列取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix Camera::GetProjection()
{
	return m_projection;
}


