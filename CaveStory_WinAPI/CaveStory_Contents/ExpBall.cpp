#include "ExpBall.h"
#include "player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include<GameEngineBase/GameEngineRandom.h>

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
		Collision->SetCollisionScale({ 35,35 });
		ExpValue = 1;
		break;
	case BallType::Mid:
		Renderer->CreateAnimation("ExpBall", "ExpBall.Bmp", 6, 11, 0.05f, true);
		Collision->SetCollisionScale({ 50,50 });
		ExpValue = 2;
		break;
	case BallType::Max:
		Renderer->CreateAnimation("ExpBall", "ExpBall.Bmp", 12, 17, 0.05f, true);
		Collision->SetCollisionScale({ 60,60 });
		ExpValue = 4;
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

	
	{
		
		float Rand = GameEngineRandom::MainRandom.RandomFloat(0, 360);


	}


}

void ExpBall::Update(float _Delta)
{
	if (false == Renderer->IsAnimation("ExpBall"))
	{
		MsgBoxAssert("Expball의 크기가 설정되지 않았습니다");
	}

	if (5.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			

			Death();
		}
	}

	if (3.5f < GetLiveTime())
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


	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			SetGravityVector(float4::UP);
			AddPos(float4::UP);
		}
	}




	if (this->Collision != nullptr)

	{
		std::vector<GameEngineCollision*> _Col;
		if (true == Collision->Collision(CollisionOrder::PlayerBody, _Col, CollisionType::CirCle, CollisionType::Rect))
		{
			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collison = _Col[i];

				Player* MyPlayer = dynamic_cast<Player*>(Collison->GetActor());

				MyPlayer->SetExp(MyPlayer->GetExp() + ExpValue);

				
				Death();

			}
		}

	}

	

}
