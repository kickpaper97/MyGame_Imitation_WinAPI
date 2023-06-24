#include "Heart.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Heart.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Heart.Bmp"), 2, 1);

	}
	{
		Renderer = CreateRenderer(RenderOrder::Bullet);
		Renderer->CreateAnimation("HeartOn", "Heart.Bmp", 0, 0, 0.05f, false);
		Renderer->CreateAnimation("HeartOff", "Heart.Bmp", 1, 1, 0.05f, false);


	}
	{
		GameEngineCollision* Collision = CreateCollision(CollisionOrder::Interct);
		Collision->SetCollisionType(CollisionType::Rect);
		Collision->SetCollisionScale({ 56,64 });
		Collision->SetCollisionPos({ 2,0 });
	}


}

void Heart::Update(float _Delta)
{
	if (0.5 <= GetLiveTime())
	{
		if(true==Renderer->IsAnimation(""))
	}

}
