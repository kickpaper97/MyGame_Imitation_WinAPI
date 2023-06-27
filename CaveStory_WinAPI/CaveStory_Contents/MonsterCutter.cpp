#include "MonsterCutter.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "ContentsEnum.h"
#include "Player.h"

#define SightLimit 300.0f

MonsterCutter::MonsterCutter()
{
}

MonsterCutter::~MonsterCutter()
{
}

void MonsterCutter::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("NpcEggs1_GreenCutter.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("NpcEggs1_GreenCutter.Bmp"), 3, 2);


	}

	{
		Renderer = CreateRenderer(RenderOrder::MiddlePlay);

		Renderer->CreateAnimation("GreenCutter_Left_Idle", "NpcEggs1_GreenCutter.bmp", 1, 1, 0.0f, false);
		Renderer->CreateAnimation("GreenCutter_Right_Idle", "NpcEggs1_GreenCutter.bmp", 4, 4, 0.0f, false);


		Renderer->CreateAnimation("GreenCutter_Left_Active", "NpcEggs1_GreenCutter.bmp", 0, 0, 0.0f, false);
		Renderer->CreateAnimation("GreenCutter_Right_Active", "NpcEggs1_GreenCutter.bmp", 3, 3, 0.0f, false);

		Renderer->CreateAnimation("GreenCutter_Left_Jump", "NpcEggs1_GreenCutter.bmp", 1, 2, 0.2f, false);
		Renderer->CreateAnimation("GreenCutter_Right_Jump", "NpcEggs1_GreenCutter.bmp", 4, 5, 0.2f, false);
		Renderer->ChangeAnimation("GreenCutter_Left_Idle");
	}
	
	 BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	 BodyCollision->SetCollisionScale({ 65, 55 });
	 BodyCollision->SetCollisionPos({ 5.0f,-30.0f });
	 BodyCollision->SetCollisionType(CollisionType::CirCle);
}

void MonsterCutter::Update(float _Delta)
{

	Monster::Update(_Delta);


	Gravity(_Delta);
	


	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			unsigned int DirColor = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);

			if (DirColor != RGB(255, 255, 255))
			{
				if (Renderer->IsAnimation("GreenCutter_Left_Jump"))
				{
					

					while (DirColor == RGB(255, 255, 255))
					{
						DirColor = GetGroundColor(RGB(255, 255, 255), float4::RIGHT);
						AddPos(float4::RIGHT);
					}
				}
				if (Renderer->IsAnimation("GreenCutter_Right_Jump"))
				{
					Renderer->ChangeAnimation("GreenCutter_Right_Active");
					while (DirColor == RGB(255, 255, 255))
					{
						DirColor = GetGroundColor(RGB(255, 255, 255), float4::LEFT);
						AddPos(float4::LEFT);
					}
				}


			}
		}
		else
		{

			if (Renderer->IsAnimation("GreenCutter_Left_Jump")&&Renderer->IsAnimationEnd())
			{

				Renderer->ChangeAnimation("GreenCutter_Left_Active");

			}
			if (Renderer->IsAnimation("GreenCutter_Right_Jump") && Renderer->IsAnimationEnd())
			{
				Renderer->ChangeAnimation("GreenCutter_Right_Active");
				
			}

			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			

			MoveReLoad += _Delta;
			
			GravityReset();
		}
	}



	{
		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);

		if (CeilingColor != RGB(255, 255, 255))
		{
			while (CeilingColor != RGB(255, 255, 255))
			{
				CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
				AddPos(float4::DOWN);
				

			}

			GravityReset();


		}
	}


	float4 Dir = Player::GetMainPlayer()->GetPos()-GetPos();

	 
	

	if (abs(Dir.X)<= 300.0f)
	{
		
		
		 if (0 < Dir.X)
		{
			Renderer->ChangeAnimation("GreenCutter_Right_Active");
			BodyCheckPos = RightBodyCheck;
		}
		else if(0 >= Dir.X)
		{
			Renderer->ChangeAnimation("GreenCutter_Left_Active");
			BodyCheckPos = LeftBodyCheck;
		}

		 if (1.0f <= MoveReLoad)
		 {
			 CanMove = true;
			 MoveReLoad = 0.0f;
		 }

		 if(true==CanMove&& abs(Dir.X) <= 200.0f)
		 {
			 if (Renderer->IsAnimation("GreenCutter_Left_Active"))
			 {
				 Renderer->ChangeAnimation("GreenCutter_Left_Jump");
				 
				 float4 JumpVector = float4::LEFT.GetUnitVectorFromDeg(250);;
				 
				 SetGravityVector(JumpVector *1.8f);
				 CanMove =false;
				
			 }

			 if (Renderer->IsAnimation("GreenCutter_Right_Active"))
			 {
				 Renderer->ChangeAnimation("GreenCutter_Right_Jump");

				 float4 JumpVector = float4::RIGHT.GetUnitVectorFromDeg(290);;

				 SetGravityVector(JumpVector *1.8f);
				 CanMove = false;


			 }


			 
		 }

	}
		
	else
	{
		if (0 < Dir.X)
		{
			Renderer->ChangeAnimation("GreenCutter_Right_Idle");
			BodyCheckPos = RightBodyCheck;
		}
		else
		{
			Renderer->ChangeAnimation("GreenCutter_Left_Idle");
			BodyCheckPos = LeftBodyCheck;
		}
	}
}


void MonsterCutter::Render(float _Delta)
{

	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	//{
	//	
	//	std::string Text = "";
	//	Text += "플레이어 테스트 값 : ";
	//	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

	//	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

	//}

	//{
	//	
	//	std::string Text = "";
	//	Text += "GrivityVector 값 : ";
	//	Text += std::to_string(GetGravityVector().Y);

	//	TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));

	//}


	//{
	//	
	//	std::string Text = "";
	//	Text += "MovePos 값 : ";
	//	Text += std::to_string(GetGravityVector().Y);

	//	TextOutA(dc, 2, 32, Text.c_str(), static_cast<int>(Text.size()));

	//}

	//CollisionData Data;

	//Data.Pos = ActorCameraPos();
	//Data.Scale = { 5,5 };
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//Data.Pos = ActorCameraPos() + LeftBodyCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//Data.Pos = ActorCameraPos() + RightBodyCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


	//Data.Pos = ActorCameraPos() + UpCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


}
