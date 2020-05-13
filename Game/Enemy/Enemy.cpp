//======================================================
// File Name	: Enemy.h
// Summary	: �G�l�~�[
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Enemy.h"

#include <DirectXTK\CommonStates.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameWindow\GameWindow.h>

#include <Game\Camera\Camera.h>

// �v�l�Ԋu�i�P�ʁF�b�j
const float Enemy::THINK_INTERVAL = 0.4f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag"></param>
Enemy::Enemy(const ObjectTag tag)
	: IGameObject(tag)
	, m_models{nullptr}
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Enemy::Initialize(int x, int y)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);

	

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void Enemy::Update(const DX::StepTimer & timer)
{
	timer;
}


/// <summary>
///�`��
/// </summary>
/// <param name="timer"></param>
void Enemy::Render(const DX::StepTimer & timer)
{
	timer;
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();


	if (!gameWindow || !m_models[NORMAL] ) return;

	

	// ���[���h�s����쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// ���f���̕`��i�W�����v�p�[�c��t���Ă��邩�ǂ����Ń��f�����Ⴄ�j
	m_models[NORMAL]->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());
}

/// <summary>
/// �Փˌ�̏���
/// </summary>
/// <param name="object"></param>
void Enemy::OnCollision(IGameObject * object)
{
	object;
}

/// <summary>
/// ���f���ݒ�
/// </summary>
/// <param name="modelType"></param>
/// <param name="model"></param>
void Enemy::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

