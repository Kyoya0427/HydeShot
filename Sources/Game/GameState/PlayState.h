#pragma once

#include <memory>

#include "GameState.h"


class DebugCamera;
class GridFloor;
class InfoWindow;
class CollisionManager;
class ObjectManager;
class GameWindow;



class PlayState: public GameState
{

public:
	PlayState();

public:
	virtual ~PlayState();


public:
	void Initialize() override;
	void Update(float elapsedTime) override;
	void Render() override;
	void Finalize() override;

private:
	// ゲーム画面のビューポート
	D3D11_VIEWPORT                          m_viewportGame;
	// 情報画面のビューポート
	D3D11_VIEWPORT                          m_viewportInfo;
	// 情報ウィンドウ
	std::unique_ptr<InfoWindow>             m_infoWindow;

	std::unique_ptr<GameWindow>				m_gameWindow;
	//コライダーマネージャー
	std::unique_ptr<CollisionManager>       m_collisionManager;
	// ゲームオブジェクトマネージャー
	std::unique_ptr<ObjectManager>          m_objectManager;
};
