//======================================================
// File Name	: PlayState.h
// Summary	: プレイステイト
// Author		: Kyoya Sakamoto
//======================================================
#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>
#include <SimpleMath.h>

#include <Game\Collider\CollisionManager.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Player\PlayerManager.h>
#include <Game\Player\Player.h>

#include <Game\Stage\StageManager.h>


#include <Utils\GameContext.h>

#include <Framework\DeviceResources.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	: IGameState()
	, m_collisionManager()
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
	//デバイス取得
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//コライダーマネジャー生成
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//モデルファイル先指定
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//ステージマネージャー生成
	m_stageManager = std::make_unique<StageManager>();
	m_stageManager->Initialize();

	//TPSカメラ生成
	m_tpsCamera = std::make_unique<TPSCamera>();
	m_tpsCamera;
	GameContext().Register<TPSCamera>(m_tpsCamera);

	//プレイヤーマネージャー生成
	m_playerManager = std::make_unique<PlayerManager>();
	m_playerManager->Initialize();
	GameContext().Register<Player>(m_playerManager->GetPlayer());

	
	m_collisionManager->AllowCollision("Player", "Ground");

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	//ポーズ画面
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	m_stageManager->Update(timer);
	m_tpsCamera->Update(timer);
	m_playerManager->Update(timer);
	m_collisionManager->DetectCollision();
	
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	
	m_stageManager->Render(timer);
	m_playerManager->Render(timer);
	m_tpsCamera->Render(timer);
}

/// <summary>
/// 終了
/// </summary>
void PlayState::Finalize()
{

}
