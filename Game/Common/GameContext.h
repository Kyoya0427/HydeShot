//======================================================
// File Name	: GameContext.h
// Summary		: �Q�[���R���e�L�X�g
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include "ServiceLocator.h"

class GameContext final
{
public:
	//�o�^
	template<typename Context, typename ConcreteContext>
	static void Register(ConcreteContext* context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//�o�^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>& context)
	{
		ServiceLocator<Context>::Register(context);
	}

	//�o�^
	template<typename Context, typename ConcreteContext>
	static void Register(std::unique_ptr<ConcreteContext>&& context)
	{
		ServiceLocator<Context>::Register(std::move(context));
	}
	
	//�擾
	template<typename Context>
	static Context* Get()
	{
		return ServiceLocator<Context>::Get();
	}

	//���
	template<typename Context>
	static void Reset()
	{
		ServiceLocator<Context>::Reset();
	}
};
