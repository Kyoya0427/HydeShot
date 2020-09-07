//======================================================
// File Name	: GameContext.h
// Summary		: ÉQÅ[ÉÄÉRÉìÉeÉLÉXÉg
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include "ServiceLocator.h"

class GameContext final
{
public:
	//ìoò^
	template<typename Context, typename ConcreteContext>
	static void Register(ConcreteContext* context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//ìoò^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>& context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//ìoò^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>&& context)
	{
		ServiceLocator<Context>::Register(std::move(context));
	}
	
	//éÊìæ
	template<typename Context>
	static Context* Get()
	{
		return ServiceLocator<Context>::Get();
	}

	//âï˙
	template<typename Context>
	static void Reset()
	{
		ServiceLocator<Context>::Reset();
	}
};
