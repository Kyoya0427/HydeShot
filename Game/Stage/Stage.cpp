//======================================================
// File Name	: Stage.
// Summary	: ステージクラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Stage.h"

#include <fstream>
#include <sstream>

#include <Effects.h>
#include <DirectXTK\CommonStates.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\IGameObject.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Stage::Stage()
	: m_floors{nullptr}
	, m_stageData{0}
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	// モデルデータの読み込み
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_floorModels[Floor::NORMAL]           = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_00.cmo", fx);
	m_floorModels[Floor::WATER]            = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_01.cmo", fx);

	// 床のタスク生成
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			std::unique_ptr<Floor> pFloor = std::make_unique<Floor>();
			m_floors[j][i] = pFloor.get();
			m_floors[j][i]->Initialize(this, i, j);
			GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(pFloor));
			// 各状態のモデルを設定
			m_floors[j][i]->SetModel(Floor::NORMAL, m_floorModels[Floor::NORMAL].get());
			m_floors[j][i]->SetModel(Floor::WATER, m_floorModels[Floor::WATER].get());
		}
	}
}

Floor * Stage::GetFloor(int x, int y)
{
	if (x >= 0 && x < STAGE_W && y >= 0 && y < STAGE_H)
	{
		return m_floors[y][x];
	}
	return nullptr;
}

bool Stage::LoadStageData(wchar_t * fname)
{
	std::wstring str;
	// ファイルのオープン
	std::wifstream ifs(fname);
	//----- ステージデータ -----//
	// ヘッダ文字列
	std::wstring stageHeadName = L"STAGE";
	// ヘッダ部分までシーク
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, stageHeadName.size(), stageHeadName) == 0)
		{
			break;
		}
	}
	// ステージデータの読み込み
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.stage[i][j] = std::stoi(tmp);
		}
	}
	//----- ステージ上のオブジェクトデータ -----//
	// ヘッダ文字列
	std::wstring objectHeadName = L"OBJECT";
	// ファイルポインタを先頭へシーク
	ifs.clear();
	ifs.seekg(0);
	// ヘッダ部分までシーク
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}
	// オブジェクトデータの読み込み
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.object[i][j] = std::stoi(tmp);
		}
	}
	// ファイルのクローズ
	ifs.close();
	return true;
}

void Stage::SetStageData()
{
	// 床を元の状態に戻す
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			m_floors[j][i]->SetState(static_cast<Floor::State>(m_stageData.stage[j][i]));
		}
	}

	//----- 各ゲームオブジェクトの生成 -----//

	// ステージ上のオブジェクトを配置する
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			// オブジェクトの種類によりタスク生成する
			switch (m_stageData.object[j][i])
			{
			case OBJECT_ID::PLAYER:	// プレイヤー
				SetPlayerPos(i, j);
				break;

		
			case OBJECT_ID::ENEMY:	// 敵２
				SetEnemyPos(i, j);
				break;
			}
		}
	}
}



void Stage::SetPlayerPos(int x, int y)
{
	m_playerPos = Vector2((float)x, (float)y);
}

void Stage::SetEnemyPos(int x, int y)
{
	m_enemyPos = Vector2((float)x, (float)y);
}

DirectX::SimpleMath::Vector2& Stage::GetPlayerPos()
{
	
	return m_playerPos;
}

DirectX::SimpleMath::Vector2& Stage::GetEnemyPos()
{
	return m_enemyPos;
}






