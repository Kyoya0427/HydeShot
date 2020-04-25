#pragma once
class StageCSV
{
public:
	StageCSV();
	~StageCSV();

	// �X�e�[�W�̑傫��
	static const int STAGE_W = 10;
	static const int STAGE_H = 10;
	// �X�e�[�W�f�[�^�̍\����
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};
	// �X�e�[�W�f�[�^
	StageData m_stageData;
	// �X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	bool LoadStageData(wchar_t* fname);

};

