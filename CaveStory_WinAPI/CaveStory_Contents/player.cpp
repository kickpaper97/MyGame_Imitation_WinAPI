#include "Player.h"
#include"ContentsEnum.h"
#include "PlayUIManager.h"

#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <CaveStory_Contents/Bullet.h>
#include<GameEngineCore/GameEngineCollision.h>

#define MaxEXP 100
#define BulletIntervalTime 0.05f


Player* Player::MainPlayer = nullptr;

Player::Player()
{
	MainPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("MyChar.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MyChar.bmp"), 15, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bullet_Effect.Bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Hover_Effect.bmp"), 3, 1);





		//FolderPath.MoveChild("Resources\\Texture\\");

		//ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		FilePath.MoveParentToExistsChild("Texture");
		FilePath.MoveChild("Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Arms.Bmp"), 6, 1);
		
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::MiddlePlay);




		MainRenderer->CreateAnimation("Left_Idle", "MyChar.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Idle", "MyChar.bmp", 15, 15, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Run", "MyChar.bmp", 1, 4, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "MyChar.bmp", 16, 19, 0.1f, true);

		MainRenderer->CreateAnimation("Left_Jump", "MyChar.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Jump", "MyChar.bmp", 18, 18, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Fall", "MyChar.bmp", 1, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Fall", "MyChar.bmp", 16, 16, 0.1f, false);




		MainRenderer->CreateAnimation("Left_UP_Idle", "MyChar.bmp", 5, 5, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Up_Idle", "MyChar.bmp", 20, 20, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Up_Run", "MyChar.bmp", 6, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Up_Run", "MyChar.bmp", 21, 24, 0.1f, true);


		MainRenderer->CreateAnimation("Left_Down_Run", "MyChar.bmp", 10, 10, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Down_Run", "MyChar.bmp", 25, 25, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Up_Jump", "MyChar.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Right_UP_Jump", "MyChar.bmp", 21, 21, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Down_Jump", "MyChar.bmp", 10, 10, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Down_Jump", "MyChar.bmp", 25, 25, 0.1f, false);


		MainRenderer->CreateAnimation("Left_Back", "MyChar.bmp", 11, 11, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Back", "MyChar.bmp", 26, 26, 0.1f, false);





		MainRenderer->ChangeAnimation("Left_Idle");
		MainRenderer->SetScaleRatio(4.0f);
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionPos({ 0,-32 });
		BodyCollision->SetCollisionScale({ 40, 54 });
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		ArmRenderer = CreateRenderer(RenderOrder::FrontPlay);
		ArmRenderer->CreateAnimation("Left_Arm", "Arms.Bmp", 0, 0, 0.0f, false);
		ArmRenderer->CreateAnimation("Right_Arm", "Arms.Bmp", 1, 1, 0.0f, false);

		ArmRenderer->CreateAnimation("Left_Up_Arm", "Arms.Bmp", 2, 2, 0.0f, false);
		ArmRenderer->CreateAnimation("Right_Up_Arm", "Arms.Bmp", 3, 3, 0.0f, false);

		ArmRenderer->CreateAnimation("Left_Down_Arm", "Arms.Bmp", 4, 4, 0.0f, false);
		ArmRenderer->CreateAnimation("Right_Down_Arm", "Arms.Bmp", 5, 5, 0.0f, false);


		ArmRenderer->SetRenderPos({ 10,0 });
		ArmRenderer->ChangeAnimation("Left_Arm");
		ArmRenderer->SetScaleRatio(4.0f);

	}

	{
		
	}

	
	

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;

}


void Player::Update(float _Delta)
{

	if (true==PlayUIManager::UI->GetTextBoxIsUpdate())
	{
		MovePos = float4::ZERO;
		ChanageState(PlayerState::Idle);
		return;
	}

	
	{
		 static GameEngineRenderer* CheckBulletEffect = nullptr;


		
		 if (nullptr != CheckBulletEffect)
		 {
			 if (true == CheckBulletEffect->IsAnimationEnd())
			 {
			
			 CheckBulletEffect->Death();
			 CheckBulletEffect = nullptr;
			 }
			 

		 }

		if (true == GameEngineInput::IsDown('X'))
		{
	
			Bullet* NewBullet = GetLevel()->CreateActor<Bullet>(RenderOrder::Bullet);
			GameEngineRenderer* NewBulletEffect =CreateRenderer(RenderOrder::Bullet);
			NewBulletEffect->CreateAnimation("BulletEffect", "Bullet_Effect.Bmp", 0, 4, 0.05f, false);
			NewBullet->SetPos(GetPos());
			NewBullet->SetDamage(PlayerLevel);
			NewBullet->SetGroundTexture(GetGroundTexture());
			if (Dir == PlayerDir::Right&&Look==PlayerLook::Middle)
			{
				NewBullet->AddPos({ 40,-20 });
				NewBulletEffect->SetRenderPos({ 40,-20 });


			}
			else if (Dir == PlayerDir::Left && Look == PlayerLook::Middle)
			{
				NewBullet->AddPos({ -40,-20 });
				NewBulletEffect->SetRenderPos({ -40,-20 });

			}
			if (Look == PlayerLook::Up)
			{
				if (Dir == PlayerDir::Right)
				{
					NewBullet->AddPos({ 40,-20 });
					NewBulletEffect->SetRenderPos({ 40,-20 });


				}
				else if (Dir == PlayerDir::Left )
				{
					NewBullet->AddPos({ -40,-20 });
					NewBulletEffect->SetRenderPos({ -40,-20 });

				}
			}
			if (Look == PlayerLook::Down)
			{
				if (Dir == PlayerDir::Right)
				{
					NewBullet->AddPos({ 40,-20 });
					NewBulletEffect->SetRenderPos({ 40,-20 });


				}
				else if (Dir == PlayerDir::Left )
				{
					NewBullet->AddPos({ -40,-20 });
					NewBulletEffect->SetRenderPos({ -40,-20 });

				}
			}
			NewBullet->SetDir(Look,Dir);
	
			
			NewBulletEffect->ChangeAnimation("BulletEffect");
	
			CheckBulletEffect = NewBulletEffect;
			
		}

	
	}




	if (true == GameEngineInput::IsDown(VK_NUMPAD1))
	{
		PlayerLevel = 1;

	}
	if (true == GameEngineInput::IsDown(VK_NUMPAD2))
	{
		PlayerLevel = 2;
	}
	if (true == GameEngineInput::IsDown(VK_NUMPAD3))
	{
		PlayerLevel = 3;

	}

	if (true == GameEngineInput::IsDown('Y'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		DebugMode = !DebugMode;
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	StateUpdate(_Delta);
	CameraFocus();

}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Hover:
		return HoverUpdate(_Delta);
	case PlayerState::Search:
		return SearchUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Hover:
			HoverStart();
			break;
		case PlayerState::Search:
			SearchStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	

	bool ChangeDir = false;
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	if (true == GameEngineInput::IsDown(VK_LEFT)|| true == GameEngineInput::IsFree(VK_RIGHT))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}
	if (true == GameEngineInput::IsDown(VK_RIGHT) || true == GameEngineInput::IsFree(VK_LEFT))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;

	}/*
	if (true == GameEngineInput::IsPress(VK_UP))
	{
		Look = PlayerLook::Up;

		ChangeAnimationState(CurState);
		
	}
	if (true == GameEngineInput::IsPress(VK_DOWN) && float4::ZERO == GetGravityVector())
	{
		Look = PlayerLook::Down;

		ChangeAnimationState(CurState);
	}*/

	


	//if (true == GameEngineInput::IsPress(VK_LEFT) && true == GameEngineInput::IsUp('D') /*&& Dir == PlayerDir::Right*/)
	//{
	//	Dir = PlayerDir::Left;
	//}

	//if (true == GameEngineInput::IsPress(VK_RIGHT) && true == GameEngineInput::IsUp('A') /*&& Dir == PlayerDir::Left*/)
	//{
	//	Dir = PlayerDir::Right;
	//}



}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";

		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	switch (Look)
	{
	case PlayerLook::Up:
		AnimationName += "Up_";
		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::BackPlay));

		if (Dir == PlayerDir::Left)
		{
			ArmRenderer->SetRenderPos({ 30,-4 });
		}
		else if (Dir == PlayerDir::Right)
		{
			ArmRenderer->SetRenderPos({ 30,4 });
		}
		ArmRenderer->ChangeAnimation(AnimationName + "Arm");
		break;
	case PlayerLook::Middle:

		AnimationName += "";

		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::FrontPlay));
		if (Dir == PlayerDir::Left)
		{
			ArmRenderer->SetRenderPos({ -28,-12 });
		}
		else if (Dir == PlayerDir::Right)
		{
			ArmRenderer->SetRenderPos({ 24,-12 });
		}
		ArmRenderer->ChangeAnimation(AnimationName + "Arm");
		break;
	case PlayerLook::Down:
		AnimationName += "Down_";
		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::BackPlay));
		if (Dir == PlayerDir::Left)
		{
			ArmRenderer->SetRenderPos({ -34,-4 });
		}
		else if (Dir == PlayerDir::Right)
		{
			ArmRenderer->SetRenderPos({ 30,-4 });
		}
		ArmRenderer->ChangeAnimation(AnimationName + "Arm");
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelStart()
{
	MainPlayer = this;
}
void Player::Render(float _Delta) 
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	if(true==DebugMode)
	{
		{
		deltacheck += _Delta;
		std::string Text = "";
		Text += "플레이어 테스트 값 : ";
		Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);

		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));

		}

		{
			deltacheck += _Delta;
			std::string Text = "";
			Text += "GrivityVector 값 : ";
			Text += CurState;

			TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));

		}


		{
			deltacheck += _Delta;
			std::string Text = "";
			Text += "MovePos 값 : ";
			Text += std::to_string(MovePos.X);
			Text += " / ";
			Text += std::to_string(MovePos.Y);

			TextOutA(dc, 2, 60, Text.c_str(), static_cast<int>(Text.size()));

		}

		{
			deltacheck += _Delta;
			std::string Text = "";
			Text += "LOOK 값 : ";
			Text += std::to_string((int)Look);

			TextOutA(dc, 2,80, Text.c_str(), static_cast<int>(Text.size()));

		}

		CollisionData Data;

		Data.Pos = ActorCameraPos();
		Data.Scale = { 5,5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + LeftBodyCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + RightBodyCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = ActorCameraPos() + UpCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());



	}
}