
#include "InfoWindow.h"

#include <DirectXTK\WICTextureLoader.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\ObjectManager.h>

#include <Game/UI/NeuralNetworkData.h>
#include <Game/UI/UiBg.h>
#include <Game/UI/SelectStateUi.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

InfoWindow::InfoWindow()
{
}

InfoWindow::~InfoWindow()
{

}

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

void InfoWindow::Update(const DX::StepTimer & timer)
{
	timer;
}

void InfoWindow::Render()
{
}

void InfoWindow::OnCollision(GameObject* object)
{
	object;
}
