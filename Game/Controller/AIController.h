//======================================================
// File Name	: AIController.h
// Summary		: ＡＩコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <map>

#include <Game/Controller/CharacterController.h>

#include <Game/CharaState/Attack.h>
#include <Game/CharaState/WallAvoid.h>
#include <Game/CharaState/Search.h>

class RuleBased;
class NeuralNetworkManager;
class Ai;

class AIController : public  CharacterController
{
public:
	enum class AiType
	{
		RULEBASED,
		NEURALNETWORK,
	
		NUM
	};

public:
	//コンストラク
	AIController(Character* character, Character* enemy);
	//デストラクタ
	~AIController();

public:
	//更新
	void Update(const DX::StepTimer& timer) override;
	//デバック描画
	void Render();

public:
	//攻撃にステイトを変更
	void ChangeAttackState();
	//サーチにステイトを変更
	void ChangeSearchState();
	//壁回避にステイトを変更
	void ChangeWallAvoidState();

public:
	using AiGroupList	  = std::map<AiType, std::unique_ptr<Ai>>;

public:
	//移動速度
	static const float  MOVE_SPEED;
	//回転速度
	static const float  ROT_SPEED;
	//最大距離
	static const float MAX_DISTANCE;
	//ショットインターバル
	static const float  SHOT_INTERVAL;
	//ステートインターバル
	static const float  STATE_INTERVAL;

	static const int    MODE_COUNT = 7;

private:
	//Aiマネージャー
	AiGroupList                             m_aiManager;
	//敵キャラ
	Character*                              m_enemy;
	//ステイト変更インターバル
	float                                   m_stateInterval;

	CharaStateID                            m_state;
	//攻撃ステート
	std::unique_ptr<Attack>                 m_attack;
	//サーチステート
	std::unique_ptr<Search>                 m_search;
	//壁回避ステート
	std::unique_ptr<WallAvoid>              m_wallAvoid;
	
};