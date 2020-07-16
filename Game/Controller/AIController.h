//======================================================
// File Name	: AIController.h
// Summary		: ＡＩコントローラー
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <map>

#include <Game/Controller/CharacterController.h>

class RuleBased;
class NeuralNetworkManager;
class Ai;

class AIController : public  CharacterController
{
public:
	enum  class Behavior
	{
		NONE,
		MOVE_FORWARD,	//1
		MOVE_BACKWARD,	//2
		MOVE_LEFTWARD,	//3
		MOVE_RIGHTWARD,	//4	
		SHOOT,			//5
		TURN_LEFT,		//6
		TURN_RIGHT,		//7

		NUM
	};

public:
	enum class AiType
	{
		RULEBASED,
		NEURALNETWORK,
	
		NUM
	};

public:
	enum class SearchDirection
	{
		FRONT,
		LEFT,
		RIGHT
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
	//ステイト
	Behavior                                m_state;
	//ステイト変更インターバル
	float                                   m_stateInterval;
	//ランダムモードに移行するためのカウント
	int                                     m_randMobeCount;
};