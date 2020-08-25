//======================================================
// File Name	: PlayState.cpp
// Summary		: プレイステイト
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayState.h"

#include <DirectXTK\Keyboard.h>

#include <Game\Common\DebugFont.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\Character.h>

#include <Game\GameState\GameStateManager.h>

#include <Game\Camera\Camera.h>

#include <Game\Bg\Bg.h>

#include <Game\Stage\Stage.h>
#include <Game\GameObject\Floor.h>

#include <Game\UI\InfoWindow.h>

#include <Game\Controller\PlayerController.h>
#include <Game\Controller\AIController.h>

#include <Game\Collider\CollisionManager.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

bool  PlayState::m_isDebug = false;

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
	//カメラを生成
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());
	//コライダーマネジャー生成
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());
	
	m_isDebug = true;

	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1,	    GameObject::ObjectTag::Wall);
//	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1,	    GameObject::ObjectTag::Bullet);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1,	    GameObject::ObjectTag::Sight02);
																		   
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2,	    GameObject::ObjectTag::Wall);
//	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2,	    GameObject::ObjectTag::Bullet);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2,	    GameObject::ObjectTag::Sight01);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2,	    GameObject::ObjectTag::Enemy1);
																		   
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Player,	    GameObject::ObjectTag::Wall);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Player,	    GameObject::ObjectTag::Bullet);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Player,	    GameObject::ObjectTag::Sight01);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Player,	    GameObject::ObjectTag::Enemy1);
																		   
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Bullet,	    GameObject::ObjectTag::Wall);	
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Sight01,	    GameObject::ObjectTag::Wall);	
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Sight02,	    GameObject::ObjectTag::Wall);	
	m_collisionManager->AllowCollision(GameObject::ObjectTag::WallApproach, GameObject::ObjectTag::Wall);	
	

	//ステージを生成
	m_stage = std::make_unique<Stage>();
	// ステージデータの読み込み
	m_stage->LoadStageData(L"Resources\\CSV\\Stage01.csv");
	// ステージデータの設定
	m_stage->SetStageData();
	m_stage->Initialize();
	GameContext::Register<Stage>(m_stage.get());
	
	//エネミー初期化
	m_enemy[0] = std::make_unique<Character>(GameObject::ObjectTag::Enemy1);
	m_enemy[0]->Initialize(m_stage->GetEnemyPos());
	m_enemy[0]->SetColor(Color(Colors::Blue));
	
	//エネミー初期化
//	m_enemy[1] = std::make_unique<Character>(GameObject::ObjectTag::Enemy2);
//	m_enemy[1]->Initialize(m_stage->GetPlayerPos());
//	m_enemy[1]->SetColor(Color(Colors::Red));

	m_player = std::make_unique<Character>(GameObject::ObjectTag::Player);
	m_player->Initialize(m_stage->GetPlayerPos());
	m_player->SetColor(Color(Colors::Red));

	m_aiController[0] = std::make_unique<AIController>(m_enemy[0].get(), m_player.get());
//	m_aiController[0] = std::make_unique<AIController>(m_enemy[0].get(), m_enemy[1].get());
//	m_aiController[1] = std::make_unique<AIController>(m_enemy[1].get(), m_enemy[0].get());
	m_playerControll = std::make_unique<PlayerController>(m_player.get());

	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_player));
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_enemy[0]));
//	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_enemy[1]));
	
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

	m_collisionManager->DetectCollision();

	m_aiController[0]->Update(timer);
//	m_aiController[1]->Update(timer);
	m_playerControll->Update(timer);

	
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Z))
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::X))
	{
		m_isDebug = !m_isDebug;
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void PlayState::Render()
{
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
	m_bg->Render();
	m_objectManager->GetGameOM()->Render();
	m_aiController[0]->Render();
//	m_playerControll->Render();
	spriteBach->End(); // <---スプライトの描画はここでまとめて行われている


	// ビューポートを変更する（右側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportInfo);
	spriteBach->Begin(SpriteSortMode_Deferred, state->NonPremultiplied());

	// 情報画面のオブジェクト描画
	m_infoWindow->Render();
	
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

