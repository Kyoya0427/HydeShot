//======================================================
// File Name	: Stage.h
// Summary		: �X�e�[�W�N���X
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <DirectXTK\Model.h>

#include <Game/GameObject/Floor.h>
#include <Game/GameObject/Wall.h>



class GameWindow;

class Stage
{
public:
	// �I�u�W�F�N�g�h�c
	enum OBJECT_ID
	{
		NONE,			// �Ȃ�
		PLAYER,			// �v���C���[
		ENEMY,			// �G�P
		WALL,
	};
	
	enum Map
	{
		NIX,
		NORMAL,
		OUTER_WALL,

		NUM
	};
	// �X�e�[�W�̑傫��
	static const int STAGE_W = 16;
	static const int STAGE_H = 16;

	// �X�e�[�W�f�[�^�̍\����
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};

public:
	// �R���X�g���N�^
	Stage();
	// �f�X�g���N�^
	~Stage();

public:
	// �������֐�
	void Initialize();

	// ���^�X�N�擾�֐�
	int GetFloor(int x, int y);

	// �X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	bool LoadStageData(wchar_t* fname);

	// �X�e�[�W�f�[�^�������֐�
	void SetStageData();


	void SetPlayerPos(int x, int y);
	void SetEnemyPos(int x, int y);

	DirectX::SimpleMath::Vector2& GetPlayerPos();
	DirectX::SimpleMath::Vector2& GetEnemyPos();
private:
	
	Floor*     m_floor;
	Wall*      m_wall;

	DirectX::SimpleMath::Vector2  m_playerPos;
	DirectX::SimpleMath::Vector2  m_enemyPos;
	
	// ���̃��f��
	std::unique_ptr<DirectX::Model> m_floorModels[static_cast<int>(Map::NUM)];

public:
	// �X�e�[�W�f�[�^
	StageData m_stageData;
};
