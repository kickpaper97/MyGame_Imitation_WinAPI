#include "ExpBall.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

ExpBall::ExpBall()
{
}

ExpBall::~ExpBall()
{
}

void ExpBall::SetBallType(const int _Type)
{
	BallType Type = static_cast<BallType>(_Type);

	switch (Type)
	{
	case BallType::Min:
		Renderer->CreateAnimation("ExpBall", "ExpBall.Bmp", 0, 5, 0.05f, true);
		
		Collision->SetCollisionScale({ 8,8 });
		break;
	case BallType::Mid:
		Renderer->CreateAnimation("ExpBall", "ExpBall.Bmp", 6, 11, 0.05f, true);
		Collision->SetCollisionScale({ 12,12 });
		break;
	case BallType::Max:
		Renderer->CreateAnimation("ExpBall", "ExpBall.Bmp", 12, 17, 0.05f, true);
		Collision->SetCollisionScale({ 16,16 });
		break;
	case BallType::None:
		
		break;
	default:
		break;
	}

	Renderer->ChangeAnimation("ExpBall");


}

void ExpBall::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("ExpBall.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("ExpBall.Bmp"), 6, 3);

	}

	{
		Renderer =GameEngineActor::CreateRenderer(RenderOrder::MiddlePlay);
		
	}
	{
		Collision=GameEngineActor::CreateCollision(CollisionOrder::ExpBall);
		Collision->SetCollisionType(CollisionType::CirCle);
	}

	



}

void ExpBall::Update(float _Delta)
{
	

	if (2.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			

			Death();
		}
	}

	if (1.5f < GetLiveTime())
	{
		if (true == IsUpdate())
		{
			Renderer->Off();
		}
		else
		{
			Renderer->On();
		}
	}
}
