//======================================================
// File Name	: Camera.h
// Summary	: カメラ
//======================================================
#pragma once
#include <DirectXTK\SimpleMath.h>

class Camera
{
public:
	Camera();
	~Camera();

public:
	void Initialize();

private:
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	//射影行列
	DirectX::SimpleMath::Matrix m_projection;

public:
	DirectX::SimpleMath::Matrix GetView()       { return m_view; }
	DirectX::SimpleMath::Vector3 Geteye()       { return m_eye; }
	DirectX::SimpleMath::Vector3 GetTarget()    { return m_target; }
	DirectX::SimpleMath::Matrix GetProjection() { return m_projection; }
};