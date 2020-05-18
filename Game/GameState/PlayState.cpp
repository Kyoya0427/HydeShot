//======================================================
// File Name	: PlayState.h
// Summary	: プレイステイト
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayState.h"
#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\Camera\Camera.h>

#include <Game\Stage\Stage.h>
#include <Game\Stage\Floor.h>

#include <Game\Bg\Bg.h>

#include <Game\UI\InfoWindow.h>


#include <Game\Player\Player.h>
#include <Game\Controller\PlayerController.h>

#include <Game\Enemy\Enemy.h>
#include <Game\Controller\AIController.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
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
	//カメラを生成
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());

	//ステージを生成
	m_stage = std::make_unique<Stage>();
	m_stage->Initialize();
	// ステージデータの読み込み
	m_stage->LoadStageData(L"Resources\\StageData\\Stage01.csv");
	// ステージデータの設定
	m_stage->SetStageData();
	GameContext::Register<Stage>(m_stage.get());
	//プレイヤー
	m_player = std::make_unique<Player>(IGameObject::Player);
	m_player->Initialize(m_stage->GetPlayerPos());
	m_playerController = std::make_unique<PlayerController>(m_player.get());
	//エネミー
	m_enemy = std::make_unique<Enemy>(IGameObject::Enemy);
	m_enemy->Initialize(m_stage->GetEnemyPos());
	m_aIController = std::make_unique<AIController>(m_enemy.get());
	// 情報ウィンドウ
	m_infoWindow = std::make_unique<InfoWindow>();
	m_infoWindow->Initialize();
	GameContext::Register<InfoWindow>(m_infoWindow.get());


	//ゲームウィンドウ
	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	



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
	
	m_bg->Update(timer);
	m_infoWindow->Update(timer);
	// ゲーム画面のオブジェクト更新
	m_objectManager->GetGameOM()->Update(timer);
	m_playerController->Update(timer);
	m_player->Update(timer);
	m_enemy->Update(timer);
	m_aIController->Update(timer);
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
	m_bg->Render(timer);
	// ゲーム画面のオブジェクト描画
	m_objectManager->GetGameOM()->Render(timer);
//	m_floor->Render(timer);
	m_player->Render(timer);
	m_enemy->Render(timer);
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている


	// ビューポートを変更する（右側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportInfo);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());

	// 情報画面のオブジェクト描画
	m_infoWindow->Render(timer);
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている

	auto viewport = deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);
	
}

/// <summary>
/// 終了
/// </summary>
void PlayState::Finalize()
{
	GameContext().Reset<InfoWindow>();
}

