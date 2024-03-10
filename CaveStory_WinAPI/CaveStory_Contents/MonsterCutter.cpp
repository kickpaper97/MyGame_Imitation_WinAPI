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
	Monster::Start();

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

	 SetHp(5);
	 SetMonsterSize(MonsterSize::Min);

}

void MonsterCutter::Update(float _Delta)
{

	Monster::Update(_Delta);


	 PlayerDistance = GetPlayerPos() - GetPos();
	 
	if (0.0f <= PlayerDistance.X)
	{
		Dir = MonsterDir::Right;
	}
	else
	{
		Dir = MonsterDir::Left;
	}

	StateUpdate(_Delta);
}


void MonsterCutter::Render(float _Delta)
{
	
	/*HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	{

		std::string Text = "";
		Text += "플레이어 테스트 값 : ";
		Text += std::to_string((int)State);

		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

	}

	{

		std::string Text = "";
		Text += "GrivityVector 값 : ";
		Text += std::to_string(GetGravityVector().X);
		Text += std::to_string(GetGravityVector().Y);

		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));

	}

	{

		std::string Text = "";
		Text += "GrivityVector 값 : ";
		Text += std::to_string(PlayerDistance.X);
		Text += std::to_string(PlayerDistance.Y);

		TextOutA(dc, 2, 360, Text.c_str(), static_cast<int>(Text.size()));

	}*/


}

void MonsterCutter::ChangeAnimationState(const std::string& _StateName)
{

	std::string AnimationName="GreenCutter_";

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
void MonsterCutter::StateUpdate(float _Delta)
{
	switch (State)
	{
	case CutterState::Idle:
		return IdleUpdate(_Delta);
	case CutterState::Jump:
		return JumpUpdate(_Delta);
	case CutterState::Active:
		return ActiveUpdate(_Delta);
	default:
		break;
	}

}

void MonsterCutter::ChanageState(CutterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case CutterState::Idle:
			IdleStart();
			break;
		case CutterState::Jump:
			JumpStart();
			break;
		case CutterState::Active:
			ActiveStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void MonsterCutter::IdleUpdate(float _Delta)
{
	{


		if (1.0f <= MoveReLoad)
		{
			CanMove = true;
			MoveReLoad = 0.0f;
		}


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


			GravityReset();


			if (0.0f <= PlayerDistance.X)
			{
				Dir = MonsterDir::Right;
				
			}
			else
			{
				Dir = MonsterDir::Left;
			}
			ChangeAnimationState("Idle");


			MoveReLoad += _Delta;

		}
	}
	

	if (abs(PlayerDistance.Size()) <= 400.0f)
	{
		ChanageState(CutterState::Active);
		return;
	}


}

void MonsterCutter::IdleStart()
{
	if (Dir == MonsterDir::Right)
	{
		BodyCheckPos = RightBodyCheck;
	}
	else
	{
		BodyCheckPos = LeftBodyCheck;
	}

	ChangeAnimationState("Idle");
}

void MonsterCutter::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
	if (RGB(255, 255, 255) != Color)
	{
		ChanageState(CutterState::Idle);
		return;
	}



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
				
				while (DirColor == RGB(255, 255, 255))
				{
					DirColor = GetGroundColor(RGB(255, 255, 255), float4::LEFT);
					AddPos(float4::LEFT);
				}
			}


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

}

void MonsterCutter::JumpStart()
{


	if (false == CanMove)
	{
		ChanageState(CutterState::Idle);
		return;
	}


	if (Dir == MonsterDir::Right)
	{
		float4 JumpVector = float4::RIGHT.GetUnitVectorFromDeg(290);;

		SetGravityVector(JumpVector * 1.8f);
		CanMove = false;
	}
	else
	{
		float4 JumpVector = float4::LEFT.GetUnitVectorFromDeg(250);;

		SetGravityVector(JumpVector * 1.8f);
		CanMove = false;
	}

	ChangeAnimationState("Jump");

}


void MonsterCutter::ActiveStart()
{
	ChangeAnimationState("Active");
}


void MonsterCutter::ActiveUpdate(float _Delta)
{

	if (1.0f <= MoveReLoad)
	{
		CanMove = true;
		MoveReLoad = 0.0f;
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

			GravityReset();

			if (0.0f <= PlayerDistance.X)
			{
				Dir = MonsterDir::Right;
			}
			else
			{
				Dir = MonsterDir::Left;
			}
				ChangeAnimationState("Active");

				MoveReLoad += _Delta;
		}
	}

	if (abs(PlayerDistance.Size()) > 400.0f)
	{
		ChanageState(CutterState::Idle);
		return;
	}




	if (true == CanMove && abs(PlayerDistance.X) <= 300.0f)
	{
		ChanageState(CutterState::Jump);
		return;
	}

}