//======================================================
// File Name	: Camera.h
// Summary	: �J����
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
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

public:
	DirectX::SimpleMath::Matrix GetView()       { return m_view; }
	DirectX::SimpleMath::Vector3 Geteye()       { return m_eye; }
	DirectX::SimpleMath::Vector3 GetTarget()    { return m_target; }
	DirectX::SimpleMath::Matrix GetProjection() { return m_projection; }
};