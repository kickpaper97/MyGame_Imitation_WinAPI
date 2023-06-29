#include "FieldEffect.h"

#include<GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>

FieldEffect::FieldEffect()
{
}

FieldEffect::~FieldEffect()
{
}


void FieldEffect::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}

}

int FieldEffect::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
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

