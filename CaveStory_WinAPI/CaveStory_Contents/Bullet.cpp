#include "Bullet.h"
#include "player.h"
#include"ContentsEnum.h"
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{

	
}

void Bullet::Start()
{
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

	if (0.1f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			Renderer->ChangeAnimation("BulletFire");

			if (BulletCollision->GetCollisionData().Scale != float4{ 42,42 })
			{
			BulletCollision->SetCollisionScale({ 42,42 });
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

	AddPos(Dir * _Delta * Speed);
}


void Bullet:: SetDir(const int _Look, const int _Dir)
{



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
		Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 6, 6, 0.05f, false);
		BulletCollision->SetCollisionScale({ 40, 16 });
		BulletCollision->SetCollisionPos({ 0,-4 });

		break;
	case BulletLook::Middle:
		if (PDir == BulletDir::Right)
		{
			Dir = float4::RIGHT;
			Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 7, 7, 0.05f, false);
			BulletCollision->SetCollisionScale({ 40, 16 });
			BulletCollision->SetCollisionPos({ 4,0 });

		}
		if (PDir == BulletDir::Left)
		{
			Dir = float4::LEFT;
			Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 5, 5, 0.05f, false);

			BulletCollision->SetCollisionScale({ 42, 16 });
			BulletCollision->SetCollisionPos({-4,0 });


		}
		break;
	case BulletLook::Down:
		Dir = float4::DOWN;
		Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 8, 8, 0.05f, false);
		BulletCollision->SetCollisionPos({ 0,4 });
		BulletCollision->SetCollisionScale({ 42, 16 });
		break;
	default:
		break;
	}
	
	BulletCollision->SetCollisionType(CollisionType::Rect);

	Renderer->ChangeAnimation("Bullet");
	Renderer->SetScaleRatio(4.0f);

	

}