#include "BackGround.h"
#include "ContentsEnum.h"
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
}

void BackGround::Update(float _Delta)
{
}

void BackGround::Render()
{
}

void BackGround::Release()
{
}

void BackGround::Init(const std::string& _FileName,const float _ScaleRatio)
{
	FileName = _FileName;
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Text->GetScale();

		Scale.X *= _ScaleRatio;
		Scale.Y *= _ScaleRatio;


		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
		Render->SetRenderScale(Scale);
	}
}