#include "Basil.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "ContentsEnum.h"
#include "Player.h"


Basil::Basil()
{
}

Basil::~Basil()
{

}

void Basil::Start()
{

	Monster::Start();


	if (false == ResourcesManager::GetInst().IsLoadTexture("NpcEggs1_Basil.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("NpcEggs1_Basil.Bmp"), 3, 2);


	}

	{
		Renderer = CreateRenderer(RenderOrder::MiddlePlay);
		Renderer->CreateAnimation("Basil_Left", "NpcEggs1_Basil.Bmp", 0, 2, 0.05f, true);
		Renderer->CreateAnimation("Basil_Right", "NpcEggs1_Basil.Bmp", 3, 5, 0.05f, true);

	}


	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionType(CollisionType::Rect);
		BodyCollision->SetCollisionScale({ 128.0f,56.0f });
		BodyCollision->SetCollisionPos({ 64.0f,-28.0f });

		
	}

	SetPos({ GetPlayerPos().X, 959});
	SetHp(1);
	SetMonsterSize(MonsterSize::Mid);
	Renderer->ChangeAnimation("Basil_Left");


}

void Basil::Update(float _Delta)
{
	

	Monster::Update(_Delta);

	if (MonsterDir::Left == Dir)
	{
		MovePos.X -= 1.0*_Delta;
	}
	else if (MonsterDir::Right == Dir)
	{
		MovePos.X +=1.00 * _Delta;
	}

	if (SpeedLimit <= MovePos.X)
	{
		MovePos.X = SpeedLimit;
	}
	
	
	if (GameEngineWindow::MainWindow.GetScale().hX() < GetPlayerPos().X - GetPos().X&&Dir== MonsterDir::Left)
	{

		MovePos= MovePos.LerpClimp(MovePos, float4::ZERO, 0.03f);
		
		if (MovePos.Size() < 1.0f)
		{
			MovePos = float4::ZERO;
		}

		if (MovePos == float4::ZERO)
		{
		Dir = MonsterDir::Right;

		BodyCheckPos = RightBodyCheck;
		AddPos({ 32.0f,0.0f });
		BodyCollision->SetCollisionPos({ -64.0f,-28.0f });
		Renderer->ChangeAnimation("Basil_Right");

		}
	}
	else if(GameEngineWindow::MainWindow.GetScale().hX()< GetPos().X-GetPlayerPos().X&&Dir== MonsterDir::Right)
	{


		MovePos = MovePos.LerpClimp(MovePos, float4::ZERO,  0.03f);

		if (MovePos.Size() < 1.0f)
		{
			MovePos = float4::ZERO;
		}
		if (MovePos == float4::ZERO)
		{
		Dir = MonsterDir::Left;
		AddPos({ -32.0f,0.0f });
		BodyCollision->SetCollisionPos({ 64.0f,-28.0f });
		BodyCheckPos = LeftBodyCheck;
		
		Renderer->ChangeAnimation("Basil_Left");

		}

	}


	



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color != RGB(255, 255, 255))
		{
			if (MonsterDir::Left == Dir)
			{
				Dir = MonsterDir::Right;
				MovePos = float4::ZERO;
				Renderer->ChangeAnimation("Basil_Right");
				BodyCollision->SetCollisionPos({ -64.0f,-28.0f });
				AddPos({ 96.0f,0.0f });
				
			}
			else if (MonsterDir::Right == Dir)
			{
				Dir = MonsterDir::Left;
				MovePos = float4::ZERO;
				Renderer->ChangeAnimation("Basil_Left");
				BodyCollision->SetCollisionPos({ 64.0f,-28.0f });
				AddPos({ -96.0f,0.0f });
				return;
			}

		}
		
	}

	AddPos(MovePos);

}

void Basil::Render(float _Delta)
{

	
	
}
