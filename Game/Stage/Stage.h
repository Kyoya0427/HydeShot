//======================================================
// File Name	: Stage.h
// Summary	: �X�e�[�W�N���X
//======================================================
#pragma once

#include <vector>


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
		ENEMY_1,		// �G�P
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



	//----- ���f���ւ̃|�C���^ -----//
	
	// �X�e�[�W�f�[�^
	StageData m_stageData;

};
