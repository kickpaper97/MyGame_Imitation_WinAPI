#include "TelePorter.h"
#include"player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>

TelePorter::TelePorter()
{
}

TelePorter::~TelePorter()
{
}


void TelePorter::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("TelePorter.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("TelePorter.Bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("TelePorter_Light.Bmp"), 1, 8);

	}

	{
		Renderer = CreateRenderer(RenderOrder::BackPlay);
		Renderer->CreateAnimation("TelePorterOn", "TelePorter.Bmp", 0, 0, 0.0f, false);
		Renderer->CreateAnimation("TelePorterOff", "TelePorter.Bmp", 1, 1, 0.0f, false);
		Renderer->ChangeAnimation("TelePorterOff");

		LightRenderer = CreateRenderer(RenderOrder::BackPlay);
		LightRenderer->CreateAnimation("TelePorter_Light", "TelePorter_Light.Bmp", 0, 7,0.05f, true);
		LightRenderer->ChangeAnimation("TelePorter_Light");
		LightRenderer->SetRenderPos({ 0.0f,-50.0f});
		LightRenderer->On();

	}

	{
		GameEngineCollision* Collision = CreateCollision(CollisionOrder::Potal);
		Collision->SetCollisionType(CollisionType::Rect);
		Collision->SetCollisionScale({ 64,96 });
		
	}

}

void TelePorter::Update(float _Delta)
{
	static float TimeCheck = 0.0f;
	if (true == Activate)
	{
		if (false == LightRenderer->IsUpdate())
		{
			LightRenderer->On();
		}
		Renderer->ChangeAnimation("TelePorterOn");
		Player::GetMainPlayer()->Off();
		TimeCheck += _Delta;
		if (1.0f < TimeCheck)
		{
			Activate = false;
			GameEngineCore::ChangeLevel(Destination);
			
			Player::GetMainPlayer()->On();
			Renderer->ChangeAnimation("TelePorterOff");
			Activate = false;
			TimeCheck = 0.0f;
			return;
		}
		
	}


}



void TelePorter::Teleport()
{
	if ("" == Destination)
	{
		MsgBoxAssert("TelePorter의 목적지가 설정되지 않았습니다.");
		return;
	}
	

	Activate = true;

}