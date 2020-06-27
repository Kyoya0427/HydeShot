//======================================================
// File Name	: RuleBased.h
// Summary		: �j���[�����l�b�g���[�N
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#include "RuleBased.h"

#include <Game/GameObject/Character.h>

#include <Game/Controller/AIController.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
///	�R���X�g���N�^ 
/// </summary>
RuleBased::RuleBased()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RuleBased::~RuleBased()
{
}

/// <summary>
/// �s���p�^�[����I������
/// </summary>
/// <param name="character">���@</param>
/// <param name="enemy">�G</param>
/// <returns>�I�����ꂽ�s��</returns>
AIController::Behavior RuleBased::BehaviorSelection(Character* character, Character* enemys)
{
	Vector3 chara = character->GetPosition();
	Vector3 enemy = enemys->GetPosition();
	float x = chara.x - enemy.x;
	float z = chara.z - enemy.z;

	if (character->GetEnemyContact() == true)
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


