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

#include <Game/GameState/PlayState.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag"></param>
Wall::Wall(const ObjectTag tag)
	: GameObject(tag)
	, m_model{nullptr}
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
	CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\floor01.png.png", NULL, m_texture.ReleaseAndGetAddressOf());
	m_position = Vector3((float)x, 0.0f, (float)y);
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
	Matrix world  = Matrix::CreateScale(Vector3(1.0f,10.0f,1.0f));
	world *= Matrix::CreateTranslation(m_position);

	// ���f���̕`��
	m_model->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()
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

		if (PlayState::m_isDebug)
		m_boxCollider->Draw(m_world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(), m_color, m_texture.Get(), true);

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
void Wall::SetModel(Model * model)
{
	m_model = model;
}

/// <summary>
/// �����蔻��Ɏg���T�C�Y
/// </summary>
/// <returns></returns>
Vector3 Wall::GetCollSize()
{
	return m_collSize;
}





