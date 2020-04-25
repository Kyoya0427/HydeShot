//======================================================
// File Name	: Stage.h
// Summary	: �X�e�[�W�N���X
// Date		: 2019/11/28
// Author		: Takafumi Ban
//======================================================
#pragma once

#include <vector>
#include "Floor.h"


#include <DirectXTK\Model.h>



class GameWindow;

class Stage
{
public:
	// �I�u�W�F�N�g�h�c
	enum OBJECT_ID
	{
		NONE,			// �Ȃ�
		PLAYER,			// �v���C���[
		POWERUP_PARTS,	// �p���[�A�b�v�p�[�c
		JUMP_PARTS,		// �W�����v�p�[�c
		ENEMY_1,		// �G�P
		ENEMY_2,		// �G�Q
	};
	
	// �X�e�[�W�̑傫��
	static const int STAGE_W = 10;
	static const int STAGE_H = 10;

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

	// �������֐�
	void Initialize();

	

	// ���^�X�N�擾�֐�
	Floor* GetFloor(int x, int y);

	// �X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	bool LoadStageData(wchar_t* fname);

	// �X�e�[�W�f�[�^�������֐�
	void SetStageData();

	// �X�e�[�W�f�[�^�̃��Z�b�g�֐�
	void ResetStageData();

private:
	// �����`�F�b�N�֐�
	bool CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// ���Ƀ_���[�W��^����֐�
	void DamageFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// �o�^����Ă���^�X�N�i�v���C���[�A�G�A�p�[�c�j��S�č폜����֐�
	void DeleteAllObject();

	// �ʒu����X�e�[�W�̃}�b�v�`�b�v�̈ʒu�ɕϊ�����֐�
	void ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y);

private:
	//----- �Q�[���I�u�W�F�N�g�ւ̃|�C���^ -----//

	// ���I�u�W�F�N�g�ւ̃|�C���^
	Floor* m_floors[STAGE_H][STAGE_W];
	//�p�[�c�I�u�W�F�N�g�ւ̃|�C���^�[

	//----- ���f���ւ̃|�C���^ -----//
	// ���̃��f��
	std::unique_ptr<DirectX::Model> m_floorModels[Floor::STATE_NUM];
	//�v���C���[�̃��f��
	//�p���[�A�b�v�p�[�c�̃��f��
	std::unique_ptr<DirectX::Model> m_powerupModel;
	//�W�����v�p�[�c���f��
	std::unique_ptr<DirectX::Model> m_jumpModel;
	//�G�̃��f��
	
	//�e���f��
	std::unique_ptr<DirectX::Model> m_shadowModel;

	// �X�e�[�W�f�[�^
	StageData m_stageData;

};