#include "BeetleWall.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include"ContentsEnum.h"

#define SpeedLimit 1.2f


BeetleWall::BeetleWall()
{
}

BeetleWall::~BeetleWall()
{
}


void BeetleWall::Start()
{

	Monster::Start();

	if (false == ResourcesManager::GetInst().IsLoadTexture("NpcEggs1_Beetle_Wall.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("NpcEggs1_Beetle_Wall.Bmp"), 3, 2);


	}

	{
		Renderer = CreateRenderer(RenderOrder::MiddlePlay);
		Renderer->CreateAnimation("Beetle_Wall_Left_Idle", "NpcEggs1_Beetle_Wall.Bmp", 0, 0, 0.01f, false);
		Renderer->CreateAnimation("Beetle_Wall_Right_Idle", "NpcEggs1_Beetle_Wall.Bmp", 3, 3, 0.01f, false);

		Renderer->CreateAnimation("Beetle_Wall_Left_Move", "NpcEggs1_Beetle_Wall.Bmp", 1, 2, 0.05f, true);
		Renderer->CreateAnimation("Beetle_Wall_Right_Move", "NpcEggs1_Beetle_Wall.Bmp", 4, 5, 0.05f, true);
		Renderer->ChangeAnimation("Beetle_Wall_Left_Idle");
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionScale({ 42,48 });
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	SetHp(5);
	SetMonsterSize(MonsterSize::Min);
	ChanageState(BeetleState::Idle);
}

void BeetleWall::Update(float _Delta)
{


	Monster::Update(_Delta);

	if (0.0f < Waiting)
	{
		Waiting -= _Delta;
		return;
	}
	



	

	StateUpdate(_Delta);
}

void BeetleWall::Render(float _Delta)
{



}

void BeetleWall::ChanageState(BeetleState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BeetleState::Idle:
			IdleStart();
			break;
		case BeetleState::Move:
			MoveStart();
			break;
		
		default:
			break;
		}
	}

	State = _State;
}

void BeetleWall::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BeetleState::Idle:
		return IdleUpdate(_Delta);
	case BeetleState::Move:
		return MoveUpdate(_Delta);
	default:
		break;
	}


}

void BeetleWall::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Beetle_Wall_";

	switch (Dir)
	{
	case MonsterDir::Right:
		AnimationName += "Right_";

		break;
	case MonsterDir::Left:
		AnimationName += "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	Renderer->ChangeAnimation(AnimationName);

}

void BeetleWall::IdleStart()
{
	Waiting = 2.0f;


	ChangeAnimationState("Idle");
}

void BeetleWall::MoveStart()
{
	MovePos = float4::ZERO;
	ChangeAnimationState("Move");
}

void BeetleWall::IdleUpdate(float _Delta)
{
	if (0.0f > Waiting)
	{

		BodyCollision->SetCollisionScale({ 55,50 });

		if (Dir == MonsterDir::Left)
		{
			BodyCollision->SetCollisionPos({ -3.0 });

		}
		else if (Dir == MonsterDir::Right)
		{
			BodyCollision->SetCollisionPos({ 3.0 });

		}


		ChanageState(BeetleState::Move);
		return;
	}



	Waiting -= _Delta;

	


}

void BeetleWall::MoveUpdate(float _Delta)
{

	if (Dir == MonsterDir::Left)
	{
		MovePos += float4::LEFT * _Delta;
		if (-SpeedLimit > MovePos.X)
		{
			MovePos.X = -SpeedLimit;
		}
	}
	else if (Dir == MonsterDir::Right)
	{
		MovePos += float4::RIGHT * _Delta;
		if (SpeedLimit < MovePos.X)
		{
			MovePos.X = SpeedLimit;
		}
	}



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color != RGB(255, 255, 255))
		{
			if (Dir == MonsterDir::Left)
			{
				Dir = MonsterDir::Right;
				BodyCheckPos = RightBodyCheck;

			}
			else if (Dir == MonsterDir::Right)
			{
				Dir = MonsterDir::Left;
				BodyCheckPos = LeftBodyCheck;
			}

			
			BodyCollision->SetCollisionScale({ 46,50 });
			BodyCollision->SetCollisionPos({ 0.0 });
			ChanageState(BeetleState::Idle);
			return;
		}



	}

	AddPos(MovePos);

}