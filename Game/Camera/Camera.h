//======================================================
// File Name	: Camera.h
// Summary		: �J����
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <DirectXTK/SimpleMath.h>

class Camera
{
public:
	//�R���X�g���N�^
	Camera();
	//�f�X�g���N�^
	~Camera();

public:
	//������
	void Initialize();

public:
	//�r���[�s��擾
	const DirectX::SimpleMath::Matrix& GetView()       { return m_view; }
	//���_�擾
	const DirectX::SimpleMath::Vector3& Geteye()       { return m_eye; }
	//�����_�擾
	const DirectX::SimpleMath::Vector3& GetTarget()    { return m_target; }
	//�ˉe�s��擾
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }

private:
	//�r���[�s��
	DirectX::SimpleMath::Matrix  m_view;
	//���_
	DirectX::SimpleMath::Vector3 m_eye;
	//�����_
	DirectX::SimpleMath::Vector3 m_target;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix  m_projection;

};