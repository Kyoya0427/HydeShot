//======================================================
// File Name	: Stage.
// Summary		: �X�e�[�W�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "Stage.h"

#include <fstream>
#include <sstream>
#include <string>
#include <Effects.h>

#include <DirectXTK\CommonStates.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\GameObject\GameObjectManager.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObject.h>


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Stage::Stage()
	: m_stageData{0}
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	// ���f���f�[�^�̓ǂݍ���
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_floorModels[Map::NORMAL] = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_00.cmo", fx);
	m_floorModels[Map::OUTER_WALL] = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_01.cmo", fx);
	
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			// �I�u�W�F�N�g�̎�ނɂ��^�X�N��������
			switch (m_stageData.stage[j][i])
			{
			case Map::NORMAL:
			{
				std::unique_ptr<Floor> floor = std::make_unique<Floor>();
				m_floor = floor.get();
				GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(floor));
			}
				m_floor->Initialize(i, j);
				m_floor->SetModel(m_floorModels[Map::NORMAL].get());
				break;

			case Map::OUTER_WALL:	
			{
				std::unique_ptr <Wall> wall = std::make_unique<Wall>(GameObject::ObjectTag::Wall);
				m_wall = wall.get();
				GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(wall));
			}
				m_wall->Initialize(i, j);
				m_wall->SetModel(m_floorModels[Map::OUTER_WALL].get());
				break;
			}
		}
	}
}

int Stage::GetFloor(int x, int y)
{
	if (x >= 0 && x < STAGE_W && y >= 0 && y < STAGE_H)
	{
		return m_stageData.stage[y][x];
	}
	return 0;
}

bool Stage::LoadStageData(wchar_t * fname)
{
	std::wstring str;
	// �t�@�C���̃I�[�v��
	std::wifstream ifs(fname);
	//----- �X�e�[�W�f�[�^ -----//
	// �w�b�_������
	std::wstring stageHeadName = L"STAGE";
	// �w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, stageHeadName.size(), stageHeadName) == 0)
		{
			break;
		}
	}
	// �X�e�[�W�f�[�^�̓ǂݍ���
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
	//----- �X�e�[�W��̃I�u�W�F�N�g�f�[�^ -----//
	// �w�b�_������
	std::wstring objectHeadName = L"OBJECT";
	// �t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);
	// �w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}
	// �I�u�W�F�N�g�f�[�^�̓ǂݍ���
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
	// �t�@�C���̃N���[�Y
	ifs.close();
	return true;
}

void Stage::SetStageData()
{
	//----- �e�Q�[���I�u�W�F�N�g�̐��� -----//

	// �X�e�[�W��̃I�u�W�F�N�g��z�u����
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			// �I�u�W�F�N�g�̎�ނɂ��^�X�N��������
			switch (m_stageData.object[j][i])
			{
			case OBJECT_ID::PLAYER:	// �v���C���[
				SetPlayerPos(i, j);
				break;

			case OBJECT_ID::ENEMY:	// �G�Q
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






