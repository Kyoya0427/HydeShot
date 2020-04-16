

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
