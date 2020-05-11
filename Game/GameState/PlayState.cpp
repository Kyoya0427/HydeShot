//======================================================
// File Name	: PlayState.h
// Summary	: プレイステイト
//======================================================
#include "PlayState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameState\GameStateManager.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\GameWindow\GameWindow.h>

#include <Game\UI\InfoWindow.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	: IGameState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayState::~PlayState()
{

}

/// <summary>
/// 初期化
/// </summary>
void PlayState::Initialize()
{
	// オブジェクトマネージャー生成
	m_objectManager = std::make_unique<ObjectManager>();
	// 情報ウィンドウを登録
	GameContext::Register<ObjectManager>(m_objectManager);

	// 情報ウィンドウ
	m_infoWindow = std::make_unique<InfoWindow>();
	GameContext::Register<InfoWindow>(m_infoWindow.get());

	//ゲームウィンドウ
	m_gameWindow = std::make_unique<GameWindow>();
	GameContext::Register<GameWindow>(m_gameWindow.get());

	//情報ウィンドウオブジェクトを登録
	m_objectManager->GetInfoOM()->Add(std::move(m_infoWindow));
	GameContext::Get<InfoWindow>()->Initialize();

	//ゲームウィンドウオブジェクトを登録
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

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();
	
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::RESULT_STATE);
	}

	ChangePauseState();
	// ゲーム画面のオブジェクト更新
	m_objectManager->GetGameOM()->Update(timer);
	// 情報画面のオブジェクト更新
	m_objectManager->GetInfoOM()->Update(timer);

	


}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	timer;
	DeviceResources* deviceResources = GameContext::Get<DeviceResources>();
	SpriteBatch* spriteBach = GameContext::Get<SpriteBatch>();
	CommonStates* state = GameContext::Get<CommonStates>();
	auto context = deviceResources->GetD3DDeviceContext();

	// ビューポートを変更する（左側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportGame);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// TODO: ビュー行列とプロジェクション行列を設定
	SimpleMath::Matrix viewMat, projMat;
	// ゲーム画面のオブジェクト描画


	m_objectManager->GetGameOM()->Render(timer);
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている


	// ビューポートを変更する（右側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportInfo);

	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());
	// 情報画面のオブジェクト描画
	m_objectManager->GetInfoOM()->Render(timer);
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている

	auto viewport = deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	
}

/// <summary>
/// 終了
/// </summary>
void PlayState::Finalize()
{
	GameContext::Reset<ObjectManager>();
	GameContext().Reset<GameWindow>();
	GameContext().Reset<InfoWindow>();
	m_objectManager.reset();
}

void PlayState::ChangePauseState()
{
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Escape))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PAUSE_STATE);
	}
}
