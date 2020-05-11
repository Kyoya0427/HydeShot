//======================================================
// File Name	: Player.cpp
// Summary	: プレイヤークラス
//日付け
//作成者
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
	, m_isChoice(false)
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

	m_rangeMap.attack.size = 4;
	m_rangeMap.move.size   = 4;
}


void Player::Update(const DX::StepTimer& timer)
{
	timer;
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Space) && (m_isChoice == false))
	{
		m_state = STATE::MOVE;
		m_isChoice = true;
		GetMap((int)m_position.x, (int)m_position.z, m_rangeMap.move.size, m_rangeMap.attack.size);
		MoveRange(&m_rangeMap.move, 4, 4, 4);
		m_cursorPos = m_position;
		m_rangeMap;
		m_stage;
	}

	if (m_isChoice == true)
	{
		MoveCursor();
		m_rangeMap;
	}
}

void Player::Render(const DX::StepTimer& timer)
{
	timer;
	GameWindow* gameWindow = GameContext::Get<GameWindow>();
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	

	if (!gameWindow || !m_models[ModelType::NORMAL] ) return;


	{
		// ワールド行列を作成
		Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

		// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
		m_models[ModelType::NORMAL]->Draw(deviceResources->GetD3DDeviceContext(),
			*GameContext::Get<DirectX::CommonStates>(),
			world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());

	}

	if (m_isChoice == true)
	{
		if (m_state == STATE::MOVE)
		{
			MovePhaseRender();
		}

		// ワールド行列を作成
		Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_cursorPos);

		// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
		m_models[ModelType::CURSOR]->Draw(deviceResources->GetD3DDeviceContext(),
			*GameContext::Get<DirectX::CommonStates>(),
			world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection());

	}
}

void Player::OnCollision(IGameObject* object)
{
	object;
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
			if ((sx1 + j >= 0 && sx1 + j < Stage::STAGE_W) && (sy1 + i >= 0 && sy1 + i < Stage::STAGE_H) && (m_stage->m_stageData.stage[sy1 + i][sx1 + j] == 1))
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
			if ((sx2 + j >= 0 && sx2 + j < Stage::STAGE_W) && (sy2 + i >= 0 && sy2 + i < Stage::STAGE_H) && (m_stage->m_stageData.stage[sy2 + i][sx2 + j] == 1))
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


void Player::MovePhaseRender()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();

	for (int i = 0; i < m_rangeMap.move.size * 2 + 1; i++)
	{
		for (int j = 0; j < m_rangeMap.move.size * 2 + 1; j++)
		{
			if (m_rangeMap.move.map[i][j] > 0)
			{
				int x = (j - m_rangeMap.move.size + static_cast<int>(m_position.x));
				int z = (i - m_rangeMap.move.size + static_cast<int>(m_position.z));
				Vector3 pos = Vector3(static_cast<float>(x), 0.1f, static_cast<float>(z));
				DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(pos);

				// モデルの描画（ジャンプパーツを付けているかどうかでモデルが違う）
				m_models[ModelType::SELECTION_RANGE]->Draw(deviceResources->GetD3DDeviceContext(),
					*GameContext::Get<DirectX::CommonStates>(),
					world, GameContext::Get<Camera>()->GetView(), GameContext::Get<Camera>()->GetProjection(),false, [&]()
				{
					// 床は半透明の加算合成（半透明で暗くなってしまうので）
					GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext()->OMSetBlendState(GameContext::Get<DirectX::CommonStates>()->Additive(), nullptr, 0xffffffff);
				});

			}
		}
	}
}

void Player::MoveCursor()
{
	Keyboard::KeyboardStateTracker* keyTracker = GameContext().Get<Keyboard::KeyboardStateTracker>();

	
	m_cursorPos.y = 0.15f;
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Left))
	{
		m_cursorPos.x -= 1.0;
	}
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Right))
	{
		m_cursorPos.x += 1.0;
	}
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Up))
	{
		m_cursorPos.z -= 1.0;
	}
	if (keyTracker->IsKeyReleased(DirectX::Keyboard::Down))
	{
		m_cursorPos.z += 1.0;
	}

	if (keyTracker->IsKeyReleased(DirectX::Keyboard::X))
	{
		int x = (static_cast<int>(m_cursorPos.x) - static_cast<int>(m_position.x)) + 4;
 		int y = (static_cast<int>(m_cursorPos.z) - static_cast<int>(m_position.z)) + 4;

		if (m_rangeMap.move.map[y][x] > 0)
		{
			m_position.x = m_cursorPos.x;
			m_position.z = m_cursorPos.z;
			m_isChoice = false;
		}
	}
}
