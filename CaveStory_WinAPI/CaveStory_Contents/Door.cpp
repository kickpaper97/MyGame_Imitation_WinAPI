#include "Door.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
Door::Door()
{
}

Door::~Door()
{
}

void Door::Start()
{
	if (nullptr == GameEngineSound::FindSound("door.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("door.wav"));


	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Door.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Map");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Door.Bmp"));

	}
	Renderer = CreateRenderer(RenderOrder::BackPlay);
	Renderer->SetTexture("Door.Bmp");

	{
		GameEngineCollision* Collision = CreateCollision(CollisionOrder::Door);
		Collision->SetCollisionType(CollisionType::Rect);
		Collision->SetCollisionScale({ 64,96 });
	}

	

}

void Door::Update(float _Delta)
{
	static float TimeCheck = 0.0f;
	if (true == Activate)
	{
		
		Renderer->Off();
		
		TimeCheck += _Delta;
		if (0.2f < TimeCheck)
		{
			Activate = false;
			GameEngineCore::ChangeLevel("Ending");

			return;
		}

	}

}
