#include "Bullet.h"
#include "player.h"
#include"ContentsEnum.h"
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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bullet_Effect.Bmp"), 4, 2);

	}
	{
		Renderer = CreateRenderer(RenderOrder::Play);
		Renderer->CreateAnimation("BulletFire", "Bullet_Effect.Bmp",0,3,0.05f,false);
		Renderer->ChangeAnimation("");

		
	}

	{
		BulletCollision = CreateCollision(CollisionOrder::Bullet);
		BulletCollision->SetCollisionScale({ 32, 16 });
		BulletCollision->SetCollisionType(CollisionType::Rect);
		
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
	AddPos(Dir * _Delta * Speed);

	if (0.1f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();
			Renderer->ChangeAnimation("BulletFire");

			Renderer->Death();
			Renderer = nullptr;
			Death();
		}
	}

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
		Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 5, 5, 0.05f, false);

		break;
	case BulletLook::Middle:
		if (PDir == BulletDir::Right)
		{
			Dir = float4::RIGHT;
			Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 6, 6, 0.05f, false);

		}
		if (PDir == BulletDir::Left)
		{
			Dir = float4::LEFT;
			Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 4, 4, 0.05f, false);

		}
		break;
	case BulletLook::Down:
		Dir = float4::DOWN;
		Renderer->CreateAnimation("Bullet", "Bullet_Effect.Bmp", 7, 7, 0.05f, false);

		break;
	default:
		break;
	}
	Renderer->ChangeAnimation("Bullet");
	Renderer->SetScaleRatio(4.0f);


}