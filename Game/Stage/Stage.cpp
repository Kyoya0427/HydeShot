//======================================================
// File Name	: Stage.cpp
// Summary	: ステージクラス
//======================================================
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
}

bool Stage::LoadStageData(wchar_t * fname)
{
	return false;
}

void Stage::SetStageData()
{
}

void Stage::ResetStageData()
{
}

bool Stage::CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	return false;
}

void Stage::DamageFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
}

void Stage::DeleteAllObject()
{
}

void Stage::ConvertPosToMapChip(float x, float z, int * floor_x, int * floor_y)
{
}
