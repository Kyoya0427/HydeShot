//======================================================
// File Name	: CharacterController.h
// Summary	: プレイヤークラス
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class Character : public IGameObject
{
public:
	//コンストラク
	Character(const ObjectTag tag = ObjectTag::None);
	//デストラクタ
	~Character();

public:
	//前進
	void Forward  (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//後進
	void Backward (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//左に進む
	void Leftward (DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//右に進む
	void Rightward(DirectX::SimpleMath::Vector3& vel, DirectX::SimpleMath::Vector3& rot, float speed);
	//左に旋回
	void LeftTurn (DirectX::SimpleMath::Vector3& rot, float speed);
	//右に旋回
	void RightTurn(DirectX::SimpleMath::Vector3& rot, float speed);
};