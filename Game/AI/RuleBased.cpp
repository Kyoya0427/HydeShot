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
AIController::State RuleBased::BehaviorSelection(Character* character, Character* enemy)
{
	//相対座標計算
	Vector3 charaPos = character->GetPosition();
	Vector3 enemyPos = enemy->GetPosition();
	float x = charaPos.x - enemyPos.x;
	float z = charaPos.z - enemyPos.z;

	/*if(character->GetWallContact())
		return static_cast<AIController::Behavior>(rand() % static_cast<int>(AIController::Behavior::SHOOT));


	if (!character->GetWallSightContact())
		if (character->GetEnemySightContact())
			return AIController::Behavior::SHOOT;

	if (z <= -6.0f)
		return AIController::Behavior::MOVE_FORWARD;
	if (z >= -4.0f && z <= 0.0f)
		return AIController::Behavior::MOVE_BACKWARD;

	if (x > 0.0f)
		return AIController::Behavior::MOVE_RIGHTWARD;
	if (x < 0.0f)
		return AIController::Behavior::MOVE_LEFTWARD;*/


    return AIController::State::NONE;
}

void RuleBased::Render()
{
}


