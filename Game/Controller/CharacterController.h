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
	

public:
	Character* GetCharacter() { return m_character; }
	CharaState* GetCharaState() { return m_charaState; }
	float GetShotInterval() { return m_shotInterval; }

public:
	void SetCharacter(Character* character) { m_character = character; }
	void SetCharaState(CharaState* charaState) { m_charaState = charaState; }
	void SetShotInterval(float shotInterval) { m_shotInterval = shotInterval; }

private:
	//操作するオブジェクト
	Character*                   m_character;
	//操作するオブジェクトのステイト
	CharaState*                  m_charaState;

	//ステイト変更インターバル
	float                        m_shotInterval;

};