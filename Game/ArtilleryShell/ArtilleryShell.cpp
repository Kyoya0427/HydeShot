//======================================================
// File Name	 : ArtilleryShell.cpp
// Summary	 : �v���C�X�e�C�g
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "ArtilleryShell.h"

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>


#include <Game\Collider\SphereCollider.h>
#include <Game\Collider\CollisionManager.h>
const float ArtilleryShell::MOVE_SPEED = 0.2f;

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N
/// </summary>
ArtilleryShell::ArtilleryShell(const ObjectTag tag, const Vector3& position, const Quaternion& azimuth)
	: GameObject(tag)
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	m_position = position;
	m_velocity.z = -MOVE_SPEED;
	m_velocity = Vector3::Transform(m_velocity, azimuth);
	m_radius = 0.3f;
	m_color = Colors::Silver;
	m_geometricPrimitive = GeometricPrimitive::CreateSphere(deviceContext, m_radius);

	m_collider = std::make_unique<SphereCollider>(this, m_radius);
	// �Փ˔���}�l�[�W���[�ɓo�^
	GameContext::Get<CollisionManager>()->Add("Shell", m_collider.get());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArtilleryShell::~ArtilleryShell()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="timer"></param>
void ArtilleryShell::Update(const DX::StepTimer & timer)
{
	timer;
	m_position += m_velocity;
	GameContext::Get<CollisionManager>()->Add("Shell", m_collider.get());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer"></param>
void ArtilleryShell::Render(const DX::StepTimer & timer)
{
	timer;
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateTranslation(m_position);

	m_geometricPrimitive->Draw(world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color);

}

/// <summary>
/// ����������̏���
/// </summary>
void ArtilleryShell::HitContact(GameObject* object)
{
	m_velocity = Vector3::Zero;
	Destroy(this);
}
