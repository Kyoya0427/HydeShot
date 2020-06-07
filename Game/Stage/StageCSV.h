//======================================================
// File Name	: StageCSV.h
// Summary		: �X�e�[�W���[�h
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

class StageCSV
{
public:
	StageCSV();
	~StageCSV();

public:
	// �X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	bool LoadStageData(wchar_t* fname);

public:
	// �X�e�[�W�̑傫��
	static const int STAGE_W = 15;
	static const int STAGE_H = 15;
	// �X�e�[�W�f�[�^�̍\����
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};

public:
	// �X�e�[�W�f�[�^
	StageData m_stageData;
	
	

};

