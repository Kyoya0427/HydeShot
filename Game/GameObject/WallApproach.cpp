//======================================================
// File Name	: WallApproach.cpp
// Summary		: �ǂɐڋ߂��Ă��邩
// Author		: Kyoya  Sakamoto
//======================================================
#include "WallApproach.h"

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game/Camera/Camera.h>

#include <Game/GameObject/GameObject.h>
#include <Game/GameObject/Character.h>
#include <Game/GameObject/WallApproachVelID.h>

#include <Game/Collider/CollisionManager.h>

#include <Game/GameState/PlayState.h>

const float WallApproach::FORWARD_ANGLE = 0.0f;
const float WallApproach::BACKWARD_ANGLE = -DirectX::XM_PI;
const float WallApproach::LEFT_ANGLE = DirectX::XM_PI / 2.0f;
const float WallApproach::RIGHT_ANGLE = -DirectX::XM_PI / 2.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="chara">�������Ă�L����</param>
WallApproach::WallApproach(Character* chara)
	: GameObject()
	, m_WallApproachCollider()
	, m_size()
	, m_chara(chara)
	, m_offsetAngle()
{
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();

	SetTag(ObjectTag::WallApproach);
	m_size = DirectX::SimpleMath::Vector3(0.3f, 0.1f, 0.8f);

	m_WallApproachCollider = DirectX::GeometricPrimitive::CreateBox(deviceContext, m_size);
	m_collider             = std::make_unique<BoxCollider>(this,m_size);	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WallApproach::~WallApproach()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void WallApproach::Update(const DX::StepTimer& timer)
{
	timer;
	m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::NONE);
	m_chara->SetWallDiscovery(false);

	DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_chara->GetRotation().y + m_offsetAngle);
	SetVelocity(DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -m_size.z), quaternion));
	SetPosition(m_chara->GetPosition());

	SetPosition(GetPosition() + GetVelocity());

	m_collider->SetPosition(GetPosition());

	GameContext().Get<CollisionManager>()->Add(ObjectTag::WallApproach, m_collider.get());
	
}

/// <summary>
/// �`��
/// </summary>
void WallApproach::Render()
{
	DirectX::SimpleMath::Quaternion rot    = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, m_chara->GetRotation().y + m_offsetAngle);
	DirectX::SimpleMath::Matrix rotMat     = DirectX::SimpleMath::Matrix::CreateFromQuaternion(rot);
	DirectX::SimpleMath::Matrix transMat   = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	DirectX::SimpleMath::Matrix offset     = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -m_size.z / 2.0f));

	DirectX::SimpleMath::Matrix matrix  = offset * rotMat * transMat;
	SetWorld(matrix);

	if (PlayState::m_isDebug)
	{
		m_WallApproachCollider->Draw(GetWorld(), GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), DirectX::Colors::Green, nullptr, true);
	}
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void WallApproach::OnCollision(GameObject* object)
{
	object;
	m_chara->SetWallDiscovery(true);
	if (m_offsetAngle == FORWARD_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::FORWARD);
	if (m_offsetAngle == BACKWARD_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::BACKWARD);
	if (m_offsetAngle == LEFT_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::LEFTWARD);
	if (m_offsetAngle == RIGHT_ANGLE)
		m_chara->GetWallApproachVel()->SetWallApproach(WallApproachVelID::RIGHTWARD);
}