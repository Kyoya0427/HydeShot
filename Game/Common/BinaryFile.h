//======================================================
// File Name	: BinaryFile.h
// Summary	: ファイルロード
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <memory>

class BinaryFile
{
public:
	//コンストラクタ
	BinaryFile();
	// ムーブコンストラクタ
	BinaryFile(BinaryFile&& in);

public:
	// ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

public:
	// アクセッサ
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }

protected:
	// データ
	std::unique_ptr<char[]> m_data;
	// サイズ
	unsigned int m_size;
};
