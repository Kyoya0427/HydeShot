#pragma once
class StageCSV
{
public:
	StageCSV();
	~StageCSV();

	// �X�e�[�W�̑傫��
	static const int STAGE_W = 15;
	static const int STAGE_H = 15;
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

