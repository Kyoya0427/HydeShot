

#include <fstream>
#include <sstream>

#include "StageCSV.h"


StageCSV::StageCSV()
{
}


StageCSV::~StageCSV()
{
}

bool StageCSV::LoadStageData(wchar_t * fname)
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
