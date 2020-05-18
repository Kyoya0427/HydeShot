//======================================================
// File Name	: Stage.
// Summary	: �X�e�[�W�N���X
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
	// ���f���f�[�^�̓ǂݍ���
	DirectX::EffectFactory fx(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_floorModels[Floor::NORMAL]           = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_00.cmo", fx);
	m_floorModels[Floor::WATER]            = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Models\\floorPanel_01.cmo", fx);

	// ���̃^�X�N����
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			std::unique_ptr<Floor> pFloor = std::make_unique<Floor>();
			m_floors[j][i] = pFloor.get();
			m_floors[j][i]->Initialize(this, i, j);
			GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(pFloor));
			// �e��Ԃ̃��f����ݒ�
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
	// �������̏�Ԃɖ߂�
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			m_floors[j][i]->SetState(static_cast<Floor::State>(m_stageData.stage[j][i]));
		}
	}

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






