//======================================================
// File Name	: InfoWindow.cpp
// Summary		: ���E�B���h�E
// Date			: 2020/5/12
// Author		: Kyoya Sakamoto
//======================================================
#include "InfoWindow.h"

#include <DirectXTK/WICTextureLoader.h>

#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/GameObject/GameObjectManager.h>
#include <Game/GameObject/ObjectManager.h>

#include <Game/UI/NeuralNetworkData.h>
#include <Game/UI/UiBg.h>
#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
InfoWindow::InfoWindow()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InfoWindow::~InfoWindow()
{

}

/// <summary>
/// ������
/// </summary>
void InfoWindow::Initialize()
{
	m_uiBg = std::make_unique<UiBg>();
	m_uiBg->Initialize(Vector3::Zero);
	GameContext::Get<ObjectManager>()->GetInfoOM()->Add(std::move(m_uiBg));

	m_neuralNetworkData = std::make_unique<NeuralNetworkData>();
	GameContext::Get<ObjectManager>()->GetInfoOM()->Add(std::move(m_neuralNetworkData));

	std::unique_ptr<SelectStateUi> selectStateUi = std::make_unique<SelectStateUi>();
	m_selectState = selectStateUi.get();
	GameContext::Register<SelectStateUi>(m_selectState);
	GameContext::Get<ObjectManager>()->GetInfoOM()->Add(std::move(selectStateUi));

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer"></param>
void InfoWindow::Update(const DX::StepTimer & timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void InfoWindow::Render()
{
}

/// <summary>
/// ����������̏���
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
void InfoWindow::OnCollision(GameObject* object)
{
	object;
}
