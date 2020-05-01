//======================================================
// File Name	: Player.cpp
// Summary		: プレイヤークラス
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#include "pch.h"
#include "Player.h"
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>
#include <DirectXTK\CommonStates.h>
#include <Game\GameWindow\GameWindow.h>
#include <Game\Camera\Camera.h>

#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <DirectXTK\Keyboard.h>

#include <Game\Stage\Stage.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 床との判定用の幅と高さ
const float Player::WIDTH = 0.2f;
const float Player::HEIGHT = 0.2f;



Player::Player(const ObjectTag tag)
	: IGameObject(tag)
	, m_models{ nullptr }
	
{
	
}

Player::~Player()
{

}


void Player::Initialize(int x, int y, Stage* stage)
{
	m_x = x;
	m_y = y;
	m_position = DirectX::SimpleMath::Vector3((float)x, 0.0f, (float)y);
	m_stage = stage;

	m_rangeMap.attack.size = 3;
	m_rangeMap.move.size = 3;
}


void Player::Update(const DX::StepTimer& timer)
{
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	GetMap((int)m_position.x,(int)m_position.z,m_rangeMap.move.size,m_rangeMap.attack.size);
	MoveRange(&m_rangeMap.move, 3, 3, 3);
	m_rangeMap;
}

void Player::Render(const DX::StepTimer& timer)
{
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	

	if (!gameWindow || !m_models[NORMAL] ) return;
	// ワールド行列を作成
	DirectX::SimpleMath::Matrix world =  DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
	m_models[NORMAL]->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext::Get<DirectX::CommonStates>(),
		world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());
}

void Player::OnCollision(IGameObject * object)
{

}

void Player::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

float Player::SLerap(float start, float end, float t)
{
	float rate = (sinf(3.0f*DirectX::XM_PI / 2.0f + DirectX::XM_PI * t) + 1.0f) / 2.0f;
	return start + (end - start) * rate;
}

void Player::MoveRange(Map * map, int x, int y, int step_count)
{
	if (x < 0 || x >= map->size * 2 + 1) return;
	if (y < 0 || y >= map->size * 2 + 1) return;
	if (map->map[y][x] == -1)            return;
	if (map->map[y][x] >= step_count)    return;

	map->map[y][x] = step_count;
	step_count--;

	if (step_count > 0)
	{
		MoveRange(map, x - 1, y, step_count);
		MoveRange(map, x, y - 1, step_count);
		MoveRange(map, x + 1, y, step_count);
		MoveRange(map, x, y + 1, step_count);
	}
}

void Player::AttackRange(Map * map, int x, int y, int range_count)
{
	if (x < 0 || x >= map->size * 2 + 1)return;
	if (y < 0 || y >= map->size * 2 + 1)return;
	if (map->map[y][x] == -1)          return;
	if (map->map[y][x] >= range_count) return;

	map->map[y][x] = range_count;
	range_count--;

	if (range_count > 0 && x == 5)
	{
		AttackRange(map, x, y - 1, range_count);
		AttackRange(map, x, y + 1, range_count);

	}

	if (range_count > 0 && y == 5)
	{
		AttackRange(map, x - 1, y, range_count);
		AttackRange(map, x + 1, y, range_count);
	}
}

void Player::GetMap(int x, int y, int size1, int size2) 
{
	//移動範囲
	int sx1 = x - size1;
	int sy1 = y - size1;
	
	for (int i = 0; i < size1 * 2 + 1; i++)
	{
		for (int j = 0; j < size1 * 2 + 1; j++)
		{
			if ((sx1 + j >= 1 && sx1 + j < Stage::STAGE_W) && (sy1 + i >= 1 && sy1 + i < Stage::STAGE_H) && (m_stage->m_stageData.stage[sy1 + i][sx1 + j] == 1))
			{
				m_rangeMap.move.map[i][j] = 0;
			}
			else
			{
				m_rangeMap.move.map[i][j] = -1;
			}
		}
	}

	//攻撃範囲
	int sx2 = x - size2;
	int sy2 = y - size2;

	for (int i = 0; i < size2 * 2 + 1; i++)
	{
		for (int j = 0; j < size2 * 2 + 1; j++)
		{
			if ((sx2 + j >= 1 && sx2 + j < Stage::STAGE_W) && (sy2 + i >= 1 && sy2 + i < Stage::STAGE_H) && (m_stage->m_stageData.stage[sy2 + i][sx2 + j] == 1))
			{
				m_rangeMap.attack.map[i][j] = 0;
			}
			else
			{
				m_rangeMap.attack.map[i][j] = -1;
			}
		}
	}


	
}
