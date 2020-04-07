#include <pch.h>

#include "PlayState.h"

#include <Keyboard.h>
#include <CommonStates.h>
#include <SpriteBatch.h>

#include "GameStateManager.h"

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\Collider\CollisionManager.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\DeviceResources.h>
#include <Game\Common\GameContext.h>

#include <Game\UI\InfoWindow.h>
#include <GameWindow\GameWindow.h>

#include <ADX2LE\Adx2Le.h>

using namespace DirectX;
using namespace DX;

PlayState::PlayState()
	: GameState()
{
}



PlayState::~PlayState()
{
}



void PlayState::Initialize()
{
	// オブジェクトマネージャー生成
	m_objectManager = std::make_unique<ObjectManager>();
	// 情報ウィンドウを登録

	GameContext::Register<ObjectManager>(m_objectManager);

	//コライダー
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext::Register<CollisionManager>(m_collisionManager);
	m_collisionManager->AllowCollision("Player", "Enemy01");
	m_collisionManager->AllowCollision("Player", "Enemy02");
	m_collisionManager->AllowCollision("Player", "PowerupParts");
	m_collisionManager->AllowCollision("Player", "JumpParts");
	m_collisionManager->AllowCollision("Enemy01", "Enemy01");
	m_collisionManager->AllowCollision("Enemy01", "Enemy02");
	m_collisionManager->AllowCollision("Enemy02", "Enemy02");
	// 情報ウィンドウ
	m_infoWindow = std::make_unique<InfoWindow>();
	GameContext::Register<InfoWindow>(m_infoWindow.get());
	
	m_gameWindow = std::make_unique<GameWindow>();
	GameContext::Register<GameWindow>(m_gameWindow.get());

	m_objectManager->GetInfoOM()->Add(std::move(m_infoWindow));
	GameContext::Get<InfoWindow>()->Initialize();

	m_objectManager->GetGameOM()->Add(std::move(m_gameWindow));
	GameContext::Get<GameWindow>()->Initialize();

	// ビューポートの矩形領域の設定（ゲーム画面）
	m_viewportGame = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		static_cast<float>(960),
		static_cast<float>(720)
	);
	// ビューポートの矩形領域の設定（情報画面）
	m_viewportInfo = CD3D11_VIEWPORT(
		static_cast<float>(960),
		0.0f,
		static_cast<float>(320),
		static_cast<float>(720)
	);

	GameContext::Get<Adx2Le>()->Stop();
	GameContext::Get<Adx2Le>()->Play(1);

}



void PlayState::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState("Pause");
	}
	// ゲーム画面のオブジェクト更新
	m_objectManager->GetGameOM()->Update(elapsedTime);
	// 情報画面のオブジェクト更新
	m_objectManager->GetInfoOM()->Update(elapsedTime);

	m_collisionManager->DetectCollision();
}



void PlayState::Render()
{
	DeviceResources* deviceResources = GameContext::Get<DeviceResources>();
	SpriteBatch* spriteBach = GameContext::Get<SpriteBatch>();
	CommonStates* state = GameContext::Get<CommonStates>();
	auto context = deviceResources->GetD3DDeviceContext();

	//----------------------//
	// ゲーム画面の描画 //
	//----------------------//
	// ビューポートを変更する（左側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportGame);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// TODO: ビュー行列とプロジェクション行列を設定
	SimpleMath::Matrix viewMat, projMat;
	// ゲーム画面のオブジェクト描画
	m_objectManager->GetGameOM()->Render();
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている
	//------------------------------//
	// ゲーム画面の描画（ここまで） //
	//------------------------------//

	//------------------//
	// 情報画面の描画 //
	//------------------//
	// ビューポートを変更する（右側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportInfo);

	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// 情報画面のオブジェクト描画
	m_objectManager->GetInfoOM()->Render();
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている
	
	//------------------------------//
	// 情報画面の描画（ここまで） //
	//------------------------------//
	// ビューポートを変更する（画面全体）
	auto viewport = deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[P] Pause");
	debugFont->draw();
}



void PlayState::Finalize()
{
	GameContext::Reset<ObjectManager>();
	GameContext().Reset<GameWindow>();
	GameContext().Reset<InfoWindow>();
	m_objectManager.reset();
}
