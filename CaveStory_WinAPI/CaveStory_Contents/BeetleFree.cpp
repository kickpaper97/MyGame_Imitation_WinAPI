#include "BeetleFree.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>


#include "ContentsEnum.h"
#include "Player.h"


#define SpeedLimit 1.1f
#define HSpeedLimit 0.6f
 
BeetleFree::BeetleFree()
{
}

BeetleFree::~BeetleFree()
{
}


void BeetleFree::Start()
{
	Monster::Start();

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

		Renderer->CreateAnimation("Beetle_Free_Left", "NpcEggs1_Beetle_Free.bmp", 0, 1, 0.1f, true);
		Renderer->CreateAnimation("Beetle_Free_Right", "NpcEggs1_Beetle_Free.bmp", 2, 3, 0.1f, true);


		Renderer->ChangeAnimation("Beetle_Free_Left");
	}



	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale({ 56, 46 });
	BodyCollision->SetCollisionPos({ -6.0f,4.0f });
	BodyCollision->SetCollisionType(CollisionType::Rect);


	SetMonsterSize(MonsterSize::Min);
	SetHp(5);
}

void BeetleFree::Update(float _Delta)
{
	if (false == IsSetStartY)
	{
		StartYPos = GetPos().Y;

		IsSetStartY = true;
	}



	Monster::Update(_Delta);




	//X축 이동
	{


		if (Dir == MonsterDir::Left)
		{
			MovePosX.X -= _Delta;
			if (-SpeedLimit > MovePosX.X)
			{
				MovePosX.X = -SpeedLimit;

			}

		}
		else if (Dir == MonsterDir::Right)
		{
			MovePosX.X += _Delta;

			if (SpeedLimit < MovePosX.X)
			{

				MovePosX.X = SpeedLimit;
			}
		}





		if (MonsterDir::Left == Dir && 0.0f < GetPlayerPos().X - GetPos().X)
		{
			if (false == Renderer->IsAnimation("Beetle_Free_Right"))
			{
				Renderer->ChangeAnimation("Beetle_Free_Right");
				BodyCollision->SetCollisionPos({ 6.0f,4.0f });
			}
			Dir = MonsterDir::Right;

		}
		if (MonsterDir::Right == Dir && 0.0f < GetPos().X - GetPlayerPos().X)
		{
			if (false == Renderer->IsAnimation("Beetle_Free_Left"))
			{
				Renderer->ChangeAnimation("Beetle_Free_Left");
				BodyCollision->SetCollisionPos({ -6.0f,4.0f });
			}

			Dir = MonsterDir::Left;


		}

		//Y축이동
		{

			if (HDir == HightDir::Down)
			{
				MovePosY.Y += _Delta;
				if (HSpeedLimit < MovePosY.Y)
				{
					HDir = HightDir::Up;

				}

			}
			else if (HDir == HightDir::Up)
			{
				MovePosY.Y -= _Delta;
				if (-HSpeedLimit > MovePosY.Y)
				{
					HDir = HightDir::Down;

				}
			}



		}



		float4 MovePos = MovePosX + MovePosY;

		AddPos(MovePos);

	}
}
