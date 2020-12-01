//======================================================
// File Name	: CharacterController.h
// Summary		: キャラクターコントローラー
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

#include <Game/CharaState/CharaState.h>


class Character;

class CharacterController
{
public:
	//コンストラク
	CharacterController(Character* character);
	//デストラクタ
	~CharacterController();

public:
	//更新
	virtual void Update(const DX::StepTimer& timer) = 0;
	//キャラを取得
	Character* GetCharacter();

protected:
	//操作するオブジェクト
	Character*                   m_character;
	//操作するオブジェクトのステイト
	CharaState*                  m_charaState;

	//ステイト変更インターバル
	float                        m_shotInterval;

};