//======================================================
// File Name	: Wall.cpp
// Summary		: �ǃN���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Wall.h"

#include <Game/Stage/Stage.h>

#include <DirectXTK\CommonStates.h>
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>
#include <Game/Common/DebugFont.h>

#include <Game\Camera\Camera.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\BoxCollider.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag"></param>
Wall::Wall(const ObjectTag tag)
	: GameObject(tag)
	, m_models{nullptr}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="x">x���W</param>
/// <param name="y">y���W</param>
void Wall::Initialize(int x, int y)
{
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
	m_color = Colors::Yellow;
	
	m_collSize = Vector3(0.5f, 0.5f, 0.5f);

	Vector3 size = Vector3(1.0f, 1.0f, 1.0f);
	ID3D11DeviceContext* deviceContext = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	m_boxCollider = GeometricPrimitive::CreateBox(deviceContext, size);

	m_collider = std::make_unique<BoxCollider>(this, m_collSize);
	m_collider->SetSize(m_collSize);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Wall::Update(const DX::StepTimer & timer)
{
	timer;
	GameContext().Get<CollisionManager>()->Add(ObjectTag::Wall, m_collider.get());
}

/// <summary>
/// �`��
/// </summary>
void Wall::Render()
{
	// ���[���h�s��̍쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// ���f���̕`��
	m_models->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
		, *GameContext::Get<DirectX::CommonStates>()
		, world
		, GameContext::Get<Camera>()->GetView()
		, GameContext::Get<Camera>()->GetProjection(), false, [&]()
	{
		// ���͔������̉��Z�����i�������ňÂ��Ȃ��Ă��܂��̂Łj
		GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
	});

		Matrix transMat = Matrix::CreateTranslation(m_position);

		m_world = transMat;

		m_boxCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, nullptr, true);
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 30, L"%f = X", m_position.x);
	debugFont->draw();
	debugFont->print(600, 50, L"%f = Y", m_position.y);
	debugFont->draw();
	debugFont->print(600, 70, L"%f = Z", m_position.z);
	debugFont->draw();
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object"></param>
void Wall::OnCollision(GameObject* object)
{
	object;
}

/// <summary>
/// ���f����ݒ�
/// </summary>
/// <param name="model"></param>
void Wall::SetModel(DirectX::Model * model)
{
	m_models = model;
}

/// <summary>
/// �����蔻��Ɏg���T�C�Y
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Wall::GetCollSize()
{
	return m_collSize;
}





