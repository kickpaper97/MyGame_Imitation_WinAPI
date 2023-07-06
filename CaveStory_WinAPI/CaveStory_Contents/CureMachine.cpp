#include "CureMachine.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineCollision.h>
#include<GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEnginePlatform/GameEngineSound.h>

CureMachine::CureMachine()
{
}

CureMachine::~CureMachine()
{
}

void CureMachine::Start()
{
	if (nullptr == GameEngineSound::FindSound("health_refill.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("health_refill.wav"));

		
	}


	if (false == ResourcesManager::GetInst().IsLoadTexture("CureMachine.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("CureMachine.Bmp"), 2, 1);

	}
	{
		Renderer = CreateRenderer(RenderOrder::BackPlay);
		Renderer->CreateAnimation("CureMachineOn", "CureMachine.Bmp", 0, 0, 0.05f, false);
		Renderer->CreateAnimation("CureMachineOff", "CureMachine.Bmp", 1, 1, 0.05f, false);

		
	}
	{
		GameEngineCollision* Collision = CreateCollision(CollisionOrder::CureMachine);
		Collision->SetCollisionType(CollisionType::Rect);
		Collision->SetCollisionScale({56,64});
		Collision->SetCollisionPos({ 2,0 });
	}




	
}

void CureMachine::Update(float _Delta)
{
	 if (GameEngineRandom::MainRandom.RandomInt(0, 1))
	 {
		 Renderer->ChangeAnimation("CureMachineOn");
	 }
	 else
	 {
		 Renderer->ChangeAnimation("curemaChineOff");
	 }

}
