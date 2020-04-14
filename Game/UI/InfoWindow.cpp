
#include "InfoWindow.h"

#include <DirectXTK\WICTextureLoader.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>


#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\ObjectManager.h>



InfoWindow::InfoWindow()
{
}

InfoWindow::~InfoWindow()
{

}

void InfoWindow::Initialize()
{
	//テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\bg01.png", nullptr,m_bg01Texture.GetAddressOf());

	
	
	
}

void InfoWindow::Update(const DX::StepTimer & timer)
{
	timer;
}

void InfoWindow::Render(const DX::StepTimer & timer)
{
	timer;

	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_bg01Texture.Get(), DirectX::SimpleMath::Vector2(0.0f, 0.0f));
}

void InfoWindow::OnCollision(IGameObject * object)
{
	object;
}
