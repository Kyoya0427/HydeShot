//======================================================
// File Name	: CharaStateID.h
// Summary		: キャラのステートID
// Date			: 2020/7/23
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

enum  class CharaStateID
{
	NONE,

	ATTACK,
	SEARCH,
	WALLAVOID,

	FORWARD,
	BACKWARD,
	LEFT_TURN,
	RIGHT_TURN,
	LEFTWARD,
	RIGHTWARD,
	
	NUM
};