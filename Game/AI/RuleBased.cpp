//======================================================
// File Name	: RuleBased.cpp
// Summary		: ルールベース
// Date			: 2020/6/27
// Author		: Kyoya  Sakamoto
//======================================================
#include "RuleBased.h"

#include <Game/GameObject/Character.h>

#include <Game/Controller/AIController.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
///	コンストラクタ 
/// </summary>
RuleBased::RuleBased()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RuleBased::~RuleBased()
{
}

/// <summary>
/// 行動パターンを選択する
/// </summary>
/// <param name="character">自機</param>
/// <param name="enemy">敵</param>
/// <returns>選択された行動</returns>
AIController::Behavior RuleBased::BehaviorSelection(Character* character, Character* enemys)
{
	//相対座標計算
	Vector3 chara = character->GetPosition();
	Vector3 enemy = enemys->GetPosition();
	float x = chara.x - enemy.x;
	float z = chara.z - enemy.z;


	if (character->GetEnemyContact())
		return AIController::Behavior::SHOOT;

	if (z <= -7.0f)
		return AIController::Behavior::MOVE_FORWARD;
	
	if (z >= -3.0f && z <= 0.0f)
		return AIController::Behavior::MOVE_BACKWARD;

	if (x > 0.0f)
		return AIController::Behavior::MOVE_RIGHTWARD;
	if (x < 0.0f)
		return AIController::Behavior::MOVE_LEFTWARD;


    return AIController::Behavior::NONE;
}


