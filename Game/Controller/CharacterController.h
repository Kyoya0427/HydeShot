//======================================================
// File Name	: CharacterController.h
// Summary		: キャラクターコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

#include <Game/CharaState/CharaState.h>
#include <Game/CharaState/Attack.h>
#include <Game/CharaState/WallAvoid.h>
#include <Game/CharaState/Search.h>

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

public:
	//攻撃にステイトを変更
	void ChangeAttackState();
	//サーチにステイトを変更
	void ChangeSearchState();
	//壁回避にステイトを変更
	void ChangeWallAvoidState();

protected:
	//操作するオブジェクト
	Character*                   m_character;
	//操作するオブジェクトのステイト
	CharaState*                  m_charaState;
	//攻撃ステート
	std::unique_ptr<Attack>      m_attack;
	//サーチステート
	std::unique_ptr<Search>      m_search;
	//壁回避ステート
	std::unique_ptr<WallAvoid>   m_wallAvoid;
	//ステイト変更インターバル
	float          m_shotInterval;

};