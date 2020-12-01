//======================================================
// File Name	: Camera.h
// Summary		: カメラ
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/SimpleMath.h>

class Camera
{
public:
	//コンストラクタ
	Camera();
	//デストラクタ
	~Camera();

public:
	//初期化
	void Initialize();

public:
	//ビュー行列取得
	const DirectX::SimpleMath::Matrix& GetView()       { return m_view; }
	//視点取得
	const DirectX::SimpleMath::Vector3& Geteye()       { return m_eye; }
	//注視点取得
	const DirectX::SimpleMath::Vector3& GetTarget()    { return m_target; }
	//射影行列取得
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }

private:
	//ビュー行列
	DirectX::SimpleMath::Matrix  m_view;
	//視点
	DirectX::SimpleMath::Vector3 m_eye;
	//注視点
	DirectX::SimpleMath::Vector3 m_target;
	//射影行列
	DirectX::SimpleMath::Matrix  m_projection;

};