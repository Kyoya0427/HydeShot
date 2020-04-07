#include <pch.h>

#include "TitleState.h"

#include <Keyboard.h>

#include <Common\DebugFont.h>
#include <Common\GameContext.h>
#include <Common\DeviceResources.h>
#include <WICTextureLoader.h>

#include "GameStateManager.h"

#include <Effect\EffectMask.h>

#include <ADX2LE\Adx2Le.h>

#include <BinaryFile.h>


TitleState::TitleState()
	: GameState()
	, m_pos(0,0)
	, m_pushPos(0,0)
	, m_blinkFlag(false)
{
}



TitleState::~TitleState()
{
}



void TitleState::Initialize()
{
	auto device = GameContext::Get<DX::DeviceResources>()->GetD3DDevice();
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\title.png", NULL, m_texture.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\push_space.png", NULL, m_pushTexture.ReleaseAndGetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\TitleShader.png", NULL, m_shaderTexture.ReleaseAndGetAddressOf());
	
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf());
	m_pos = DirectX::SimpleMath::Vector2(0, 0);
	m_shaderPos = DirectX::SimpleMath::Vector2(0, 0);
	m_pushPos = DirectX::SimpleMath::Vector2(430, 600);

	//GameContext::Get<EffectMask>()->Open();

	m_blink = std::make_unique<Blink>();
	m_blink->Initialize(0.16f);
	m_blink->Start();
	GameContext::Get<Adx2Le>()->Play(0);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}



void TitleState::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	m_constBuffer.time.x += elapsedTime;

	if (GameContext::Get<EffectMask>()->IsOpen() && keyState.Space)
	{
		// エフェクトマスクを閉じる
		GameContext::Get<EffectMask>()->Close();
	}
	// エフェクトマスクが閉じきったら
	if (GameContext::Get<EffectMask>()->IsClose())
	{
		// プレイへ
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Play");
	}

	SelectPartsMode(true);
	m_blink->Update(elapsedTime);
	
}



void TitleState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();

	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &m_constBuffer, 0, 0);

	m_spriteBatch->Begin(DirectX::SpriteSortMode::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [&]() {
		context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
		context->PSSetConstantBuffers(0, 1, cb);
	});
	m_spriteBatch->Draw(m_shaderTexture.Get(), m_shaderPos);
	m_spriteBatch->End();


	m_spriteBatch->Begin();

	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	
	if (m_blinkFlag == false || m_blink->GetState())
	{
		m_spriteBatch->Draw(m_pushTexture.Get(), m_pushPos);
	}

	m_spriteBatch->End();
}



void TitleState::Finalize()
{

}

void TitleState::SelectPartsMode(bool flag)
{
	m_blinkFlag = flag;
	// 点滅間隔の設定
	if (m_blinkFlag == true)
	{
		m_blink->Initialize(0.2f);
	}
	else
	{
		m_blink->Initialize(0.2f);
	}
}
