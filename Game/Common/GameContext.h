//======================================================
// File Name	: GameContext.h
// Summary		: ƒQ[ƒ€ƒRƒ“ƒeƒLƒXƒg
//======================================================
#pragma once

#include "ServiceLocator.h"

class GameContext final
{
public:
	//“o˜^
	template<typename Context, typename ConcreteContext>
	static void Register(ConcreteContext* context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//“o˜^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>& context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//“o˜^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>&& context)
	{
		ServiceLocator<Context>::Register(std::move(context));
	}
	
	//æ“¾
	template<typename Context>
	static Context* Get()
	{
		return ServiceLocator<Context>::Get();
	}

	//‰ğ•ú
	template<typename Context>
	static void Reset()
	{
		ServiceLocator<Context>::Reset();
	}
};
