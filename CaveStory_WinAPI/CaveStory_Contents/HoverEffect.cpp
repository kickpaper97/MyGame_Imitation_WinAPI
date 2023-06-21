#include "HoverEffect.h"
#include"ContentsEnum.h"
#include<GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

HoverEffect::HoverEffect()
{
}

HoverEffect::~HoverEffect()
{
}
void HoverEffect::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Hover_Effect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bullet_Effect.Bmp"), 3, 1);

	}
	{
		Renderer = CreateRenderer();
		Renderer->CreateAnimation("HoverEffect", "Hover_Effect.Bmp", 0, 2, 0.5f, false);
		Renderer->ChangeAnimation("HoverEffect");
		Renderer->SetScaleRatio(4.0f);


	}
}
