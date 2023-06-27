#include "BeetleFree.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "ContentsEnum.h"
#include "Player.h"


BeetleFree::BeetleFree()
{
}

BeetleFree::~BeetleFree()
{
}

void BeetleFree::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("NpcEggs1_Beetle_Free.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("NpcEggs1_Beetle_Free.Bmp"), 2, 2);


	}

	{
		Renderer = CreateRenderer(RenderOrder::MiddlePlay);

		Renderer->CreateAnimation("Beetle_Free_Left", "NpcEggs1_Basil.bmp", 0, 1, 0.5f, true);
		Renderer->CreateAnimation("Beetle_Free_Right", "NpcEggs1_Basil.bmp", 2, 3, 0.5f, true);


		Renderer->ChangeAnimation("Beetle_Free_Left");
	}



	GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 300, 100 });
	BodyCollsion->SetCollisionType(CollisionType::Rect);

}

void BeetleFree::Update(float _Delta)
{
	float4 PDir = Player::GetMainPlayer()->GetPos();
	float4 Dir = PDir - GetPos();

	//if(GetLevel()->GetMainCamera().<Dir.Size())
}


