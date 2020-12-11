//======================================================
// File Name	: PlayState.cpp
// Summary		: プレイステイト
// Author		: Kyoya  Sakamoto
//======================================================
#include "PlayState.h"

#include <DirectXTK/Keyboard.h>

#include <Game/Common/DebugFont.h>
#include <Game/Common/GameContext.h>
#include <Game/Common/DeviceResources.h>

#include <Game/GameObject/ObjectManager.h>
#include <Game/GameObject/GameObjectManager.h>
#include <Game/GameObject/Character.h>
#include <Game/GameObject/SelectMode.h>

#include <Game/GameState/GameStateManager.h>
#include <Game/GameState/SelectState.h>

#include <Game/Camera/Camera.h>

#include <Game/Bg/Bg.h>

#include <Game/Stage/Stage.h>

#include <Game/GameObject/Floor.h>

#include <Game/UI/InfoWindow.h>

#include <Game/Controller/PlayerController.h>
#include <Game/Controller/AIController.h>
#include <Game/Controller/AutoPlayerController.h>

#include <Game/Collider/CollisionManager.h>

bool  PlayState::m_isDebug        = false;
const float  PlayState::END_TIMER = 15.0f;

/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	: IGameState()
	, m_gameEndTimer()
{
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_tankModels[Tank::RED] = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\redTank.cmo", fx);
	m_tankModels[Tank::BLUE] = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\blueTank.cmo", fx);
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
	GameContext::Register<ObjectManager>(m_objectManager);

	m_infoWindow = std::make_unique<InfoWindow>();
	m_infoWindow->Initialize();

	//カメラを生成
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());

	
	//ステージを生成
	m_stage = std::make_unique<Stage>();
	// ステージデータの読み込み
	m_stage->LoadStageData(L"Resources\\CSV\\Stage01.csv");
	// ステージデータの設定
	m_stage->SetStageData();
	m_stage->Initialize();
	GameContext::Register<Stage>(m_stage.get());

	//当たり判定するオブジェクトタグを登録
	RegisterTheObject();

	//キャラクターを登録
	CreateCharacter();

	//ゲームウィンドウ
	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	
	// ビューポートの矩形領域の設定（ゲーム画面）
	m_viewportGame = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		static_cast<float>(SCREEN_W),
		static_cast<float>(SCREEN_H)
	);
	// ビューポートの矩形領域の設定（情報画面）
	m_viewportInfo = CD3D11_VIEWPORT(
		static_cast<float>(SCREEN_W),
		0.0f,
		static_cast<float>(WINDOW_W),
		static_cast<float>(SCREEN_H)
	);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	m_bg->Update(timer);
	m_objectManager->GetGameOM()->Update(timer);
	m_objectManager->GetInfoOM()->Update(timer);
	m_collisionManager->DetectCollision();
	m_aiController[0]->Update(timer);

	if (SelectState::GetRedMode() == SelectMode::MANUAL_PLAYER)
		m_playerControll->Update(timer);
	if (SelectState::GetRedMode() == SelectMode::AUTO_PLAYER)
		m_autoPlayerController->Update(timer);

	//A.I.同士の戦いに決着が付かない時の処理
	if (SelectState::GetSelectChara() == SelectState::SelectCharacter::ENEMY)
	{
		m_aiController[1]->Update(timer);
		m_gameEndTimer -= elapsedTime;
	}
	if (m_gameEndTimer < 0.0f)
	{
		using State = GameStateManager::GameState;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(State::RESULT_STATE);
	}
	
	Debug();
}

/// <summary>
/// 描画
/// </summary>
void PlayState::Render()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	DirectX::SpriteBatch* spriteBach = GameContext::Get<DirectX::SpriteBatch>();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	auto context = deviceResources->GetD3DDeviceContext();

	// ビューポートを変更する（左側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportGame);
	spriteBach->Begin(DirectX::SpriteSortMode_Deferred, state->NonPremultiplied());

	// TODO: ビュー行列とプロジェクション行列を設定
	DirectX::SimpleMath::Matrix viewMat, projMat;
	
	// ゲーム画面のオブジェクト描画
	m_bg->Render();
	m_objectManager->GetGameOM()->Render();
	spriteBach->End();
	
	//スプライトの描画はここでまとめて行われている


	// ビューポートを変更する（右側へ描画エリアを変更する）
	context->RSSetViewports(1, &m_viewportInfo);
	spriteBach->Begin(DirectX::SpriteSortMode_Deferred, state->NonPremultiplied());

	// 情報画面のオブジェクト描画
	m_objectManager->GetInfoOM()->Render();

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

/// <summary>
/// 当たり判定するオブジェクトタグを登録
/// </summary>
void PlayState::RegisterTheObject()
{
	//コライダーマネジャー生成
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1, GameObject::ObjectTag::Wall);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1, GameObject::ObjectTag::Bullet);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy1, GameObject::ObjectTag::Sight02);

	if (SelectState::GetSelectChara() == SelectState::SelectCharacter::ENEMY)
	{
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2, GameObject::ObjectTag::Wall);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2, GameObject::ObjectTag::Bullet);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2, GameObject::ObjectTag::Sight01);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Enemy2, GameObject::ObjectTag::Enemy1);
	}

	if (SelectState::GetSelectChara() == SelectState::SelectCharacter::PLAYER)
	{
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Player, GameObject::ObjectTag::Wall);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Player, GameObject::ObjectTag::Bullet);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Player, GameObject::ObjectTag::Sight01);
		m_collisionManager->AllowCollision(GameObject::ObjectTag::Player, GameObject::ObjectTag::Enemy1);
	}

	m_collisionManager->AllowCollision(GameObject::ObjectTag::Bullet, GameObject::ObjectTag::Wall);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Sight01, GameObject::ObjectTag::Wall);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::Sight02, GameObject::ObjectTag::Wall);
	m_collisionManager->AllowCollision(GameObject::ObjectTag::WallApproach, GameObject::ObjectTag::Wall);

}

/// <summary>
/// キャラクターを登録
/// </summary>
void PlayState::CreateCharacter()
{
	//エネミー初期化
	m_enemy[0] = std::make_unique<Character>(GameObject::ObjectTag::Enemy1);
	m_enemy[0]->SetColor(DirectX::SimpleMath::Color(DirectX::Colors::Blue));
	m_enemy[0]->SetModel(m_tankModels[Tank::BLUE].get());
	m_enemy[0]->Initialize(m_stage->GetEnemyPos());


	if (SelectState::GetSelectChara() == SelectState::SelectCharacter::ENEMY)
	{
		m_enemy[1] = std::make_unique<Character>(GameObject::ObjectTag::Enemy2);
		m_enemy[1]->SetColor(DirectX::SimpleMath::Color(DirectX::Colors::Red));
		m_enemy[1]->SetModel(m_tankModels[Tank::RED].get());
		m_enemy[1]->Initialize(m_stage->GetPlayerPos());
		m_aiController[0] = std::make_unique<AIController>(m_enemy[0].get(), m_enemy[1].get(), SelectState::GetBlueMode());
		m_aiController[1] = std::make_unique<AIController>(m_enemy[1].get(), m_enemy[0].get(), SelectState::GetRedMode());
		GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_enemy[1]));
		m_gameEndTimer = END_TIMER;
	}

	if (SelectState::GetSelectChara() == SelectState::SelectCharacter::PLAYER)
	{
		//プレイヤー初期化
		m_player = std::make_unique<Character>(GameObject::ObjectTag::Player);
		m_player->SetColor(DirectX::SimpleMath::Color(DirectX::Colors::Red));
		m_player->SetModel(m_tankModels[Tank::RED].get());
		m_player->Initialize(m_stage->GetPlayerPos());
		m_aiController[0] = std::make_unique<AIController>(m_enemy[0].get(), m_player.get(), SelectState::GetBlueMode());

		if (SelectState::GetRedMode() == SelectMode::MANUAL_PLAYER)
			m_playerControll = std::make_unique<PlayerController>(m_player.get());
		if (SelectState::GetRedMode() == SelectMode::AUTO_PLAYER)
			m_autoPlayerController = std::make_unique<AutoPlayerController>(m_player.get());
		GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_player));
	}

	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_enemy[0]));
}

/// <summary>
/// デバック表記
/// </summary>
void PlayState::Debug()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);
	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::X))
	{
		m_isDebug = !m_isDebug;
	}
}