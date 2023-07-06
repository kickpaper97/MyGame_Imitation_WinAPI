#include "Bullet.h"
#include "player.h"
#include"ContentsEnum.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#define HitWallRenderPos 35.0f

Bullet::Bullet()
{
}

Bullet::~Bullet()
{

	
}

bool Bullet::HitWallCheck()
{

	
	
		unsigned int Color = GetGroundColor(RGB(255, 255, 255),WallCheck);
		if (RGB(255, 255, 255) != Color)
		{
			Renderer->ChangeAnimation("BulletOnWall");
			
			BulletCollision->Off();
			

			if (float4::UP == Dir)
			{
				Renderer->AddRenderPos({ 0.0f,-HitWallRenderPos });
			}
			else if (float4::DOWN == Dir)
			{
				Renderer->AddRenderPos({ 0.0f,HitWallRenderPos });

			}
			else if (float4::LEFT == Dir)
			{
				Renderer->AddRenderPos({ -HitWallRenderPos,0.0f });

			}
			else if (float4::RIGHT == Dir)
			{
				Renderer->AddRenderPos({ HitWallRenderPos,0.0f });

			}


			return true;
		}
	
		return false;
}



	

void Bullet::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Bullet_Morning.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bullet_Morning.Bmp"), 2, 3);


	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Bullet_Effect.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Player\\");


		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bullet_Effect.Bmp"), 5, 2);
	}


	{
		Renderer = CreateRenderer(RenderOrder::Bullet);
		Renderer->CreateAnimation("BulletFire", "Bullet_Effect.Bmp", 0, 4, 0.05f, false);
		Renderer->CreateAnimation("BulletOnWall", "Bullet_Effect.Bmp", 5, 9, 0.05f, false);

		
	}


	
	{
		BulletCollision = CreateCollision(CollisionOrder::Bullet);
	}

	
	
}

void Bullet::Update(float _Delta)
{

	
	
	if (nullptr == Renderer->FindAnimation("Bullet"))
	{
		MsgBoxAssert("Bullet의 Dir값이 제대로 세팅되지 않았습니다.");
		return;
	}
	// Bullet자체가 


	if (Renderer->IsAnimation("BulletOnWall") )
	{

		if (false == Renderer->IsAnimationEnd())
		{
			return;
		}

		Death();
	}




	if (0.5f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			Renderer->ChangeAnimation("BulletFire");

			if (BulletCollision->GetCollisionData().Scale != float4{ 50,50 })
			{
			BulletCollision->SetCollisionScale({ 50,50 });
			BulletCollision->SetCollisionType(CollisionType::CirCle);
			}
			
			if (true != Renderer->IsAnimationEnd())
			{
				return;
			}
			
			if (true == Renderer->IsAnimationEnd())
			{
			BulletCollision->Off();

			
			BulletCollision->Death();
			Renderer->Death();

			//Renderer = nullptr;
			//BulletCollision = nullptr;
			}

			Death();
		}
	}

	if (false==HitWallCheck())
	{
	AddPos(Dir * _Delta * Speed);

	}





}


void Bullet:: SetDir(const int _Look, const int _Dir)
{

	if (0 == Level)
	{
		MsgBoxAssert("총알의 레벨이 설정되지 않았습니다.");
		return;
	}

	if (Renderer == nullptr)
	{
		MsgBoxAssert("Bullet의 렌더러가 생성되지 않았습니다.")
			return;
	}
	
	

	


	BulletDir PDir = static_cast<BulletDir>(_Dir);
	BulletLook PLook = static_cast<BulletLook>(_Look);

	switch (PLook)
	{
	case BulletLook::Up:
		Dir = float4::UP;
		WallCheck = { 0.0f,-35.0f };
		switch (Level)
		{
		case 1:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 1, 1, 0.05f, false);

			BulletCollision->SetCollisionScale({ 12.0f, 60.0f });
			BulletCollision->SetCollisionPos({ 0.0f,-2.0f });
			break;
		case 2:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 3, 3, 0.05f, false);

			BulletCollision->SetCollisionScale({ 18.0f, 60.0f});
			BulletCollision->SetCollisionPos({ 0.0f,-2.0f });
			
			break;
		case 3:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 5, 5, 0.05f, false);

			BulletCollision->SetCollisionScale({ 32.0f, 60.0f });
			BulletCollision->SetCollisionPos({ 0.0f,-2.0f});
			break;
		default:
			break;
		}

		break;
	case BulletLook::Middle:
		if (PDir == BulletDir::Right)
		{
			Dir = float4::RIGHT;
			WallCheck = { 35.0f,0.0f };
			switch (Level)
			{
			case 1:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 0, 0, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60.0f, 12.0f });
				BulletCollision->SetCollisionPos({ 2.0f,0.0f });
				break;
			case 2:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 2, 2, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60.0f, 18.0f});
				BulletCollision->SetCollisionPos({ 2.0f,0.0f });

				break;
			case 3:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 4, 4, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60, 32 });
				BulletCollision->SetCollisionPos({ 2.0f,0.0f });
				break;
			default:
				break;
			}

		}
		if (PDir == BulletDir::Left)
		{
			Dir = float4::LEFT;
			WallCheck = { -35.0f,0.0f };
			switch (Level)
			{
			case 1:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 0, 0, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60.0f, 12.0f });
				BulletCollision->SetCollisionPos({ -2.0f,0.0f });
				break;
			case 2:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 2, 2, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60.0f, 18.0f });
				BulletCollision->SetCollisionPos({ -2.0f,0.0f });
				break;
			case 3:
				Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 4, 4, 0.05f, false);

				BulletCollision->SetCollisionScale({ 60.0f, 32.0f});
				BulletCollision->SetCollisionPos({ -2.0f,0.0f });
				break;
			default:
				break;
			}


		}
		break;
	case BulletLook::Down:
		Dir = float4::DOWN;
		WallCheck = { 0.0f,35.0f };
		switch (Level)
		{
		case 1:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 1, 1, 0.05f, false);

			BulletCollision->SetCollisionScale({ 12, 60 });
			BulletCollision->SetCollisionPos({ 0,2 });
			break;
		case 2:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 3, 3, 0.05f, false);

			BulletCollision->SetCollisionScale({ 18, 60 });
			BulletCollision->SetCollisionPos({ 0,2 });
			break;
		case 3:
			Renderer->CreateAnimation("Bullet", "Bullet_Morning.Bmp", 5, 5, 0.05f, false);

			BulletCollision->SetCollisionScale({ 32, 60 });
			BulletCollision->SetCollisionPos({ 0,2 });
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
	
	BulletCollision->SetCollisionType(CollisionType::Rect);

	Renderer->ChangeAnimation("Bullet");
	
	Renderer->SetScaleRatio(2.0f);
	

}

