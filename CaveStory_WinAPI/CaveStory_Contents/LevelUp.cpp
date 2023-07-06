#include "LevelUp.h"
#include"ContentsEnum.h"
#include<GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "player.h"

LevelUp::LevelUp()
{
}

LevelUp::~LevelUp()
{
}

void LevelUp::Start()
{



	if (false == ResourcesManager::GetInst().IsLoadTexture("LevelUp.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LevelUp.Bmp"),1,2);

	}

	{
		Renderer = CreateRenderer(RenderOrder::FrontPlay);
		Renderer->CreateAnimation("LevelUp", "LevelUp.Bmp", 0, 1, 0.05f, true);
		Renderer->ChangeAnimation("LevelUp");
	}

	CreatePos = Player::GetMainPlayer()->GetPos();
}

void LevelUp::Update(float _Delta)
{
	if (1.0f <= TimeCount)
	{

		Death();
	}


	if (90.0f > CreatePos.Y - GetPos().Y)
	{
		float pos = CreatePos.Y - GetPos().Y;
		AddPos(float4::UP * 2);
	}

	TimeCount += _Delta;


}
