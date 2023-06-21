#include "FieldEffect.h"

#include<GameEngineCore/GameEngineRenderer.h>

FieldEffect::FieldEffect()
{
}

FieldEffect::~FieldEffect()
{
}


void FieldEffect::Update(float _Delta)
{


	if (nullptr != Renderer)
	{
		if (true==Renderer->IsAnimationEnd())
		{
			Death();
		}
	}
	else 
	{
		Death();
	}
}

