#include "BackGround.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineDebug.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")


BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	SetPos({ 640,360 });
	Renderer = CreateRenderer(RenderOrder::BackGround);

	DebugRenderer = CreateRenderer(RenderOrder::BackGround);

	Renderer->On();
	DebugRenderer->Off();

}

void BackGround::Update(float _Delta)
{
}


void BackGround::Release()
{
}



void BackGround::Init(const std::string& _FileName,const float _ScaleRatio)
{
	
	IsNeedBackGroundDebug = false;

	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
		float4 Scale = Texture->GetScale();

		Scale.X *= _ScaleRatio;
		Scale.Y *= _ScaleRatio;

		Renderer->SetTexture(_FileName);
		Renderer->SetRenderScale(Scale);
		SetPos({ Scale.hX(),Scale.hY() });

}

void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName, const float _ScaleRatio)
{


	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();
	

	Scale.X *= _ScaleRatio;
	Scale.Y *= _ScaleRatio;

	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);
	SetPos({ Scale.hX(), Scale.hY() });


}


void BackGround::SwitchRender()
{
	if (false == IsNeedBackGroundDebug)
	{
		return;
	}

	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}
