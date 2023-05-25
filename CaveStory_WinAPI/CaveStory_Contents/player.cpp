#include "Player.h"
#include"ContentsEnum.h"

#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <CaveStory_Contents/Bullet.h>

Player* Player::MainPlayer = nullptr;

Player::Player()
{
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




		//FolderPath.MoveChild("Resources\\Texture\\");

		//ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		FilePath.MoveParentToExistsChild("Texture");
		FilePath.MoveChild("Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Arms.Bmp"), 6, 1);
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);




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

		MainRenderer->CreateAnimation("Left_Up_Jump", "MyChar.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Right__UP_Jump", "MyChar.bmp", 21, 21, 0.1f, false);

		MainRenderer->CreateAnimation("Left_Down_Jump", "MyChar.bmp", 11, 11, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Back", "MyChar.bmp", 26, 26, 0.1f, false);


		MainRenderer->CreateAnimation("Left_Back", "MyChar.bmp", 10, 10, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Down_Jump", "MyChar.bmp", 25, 25, 0.1f, false);



		MainRenderer->ChangeAnimation("Left_Idle");
		MainRenderer->SetScaleRatio(4.0f);
	}

	{
		ArmRenderer = CreateRenderer(RenderOrder::Nomal_Arms);
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

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;

}


void Player::Update(float _Delta)
{
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
			if (true == IsJump)
			{
			JumpStart();

			}
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	PlayerDir CheckDir = PlayerDir::Max;
	Look = PlayerLook::Middle;

	bool ChangeDir = false;

	if (true == GameEngineInput::IsDown('A')||true==GameEngineInput::IsPress('A'))
	{
		CheckDir = PlayerDir::Left;
		Look = PlayerLook::Middle;
	}
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsPress('D'))
	{
		CheckDir = PlayerDir::Right;
		Look = PlayerLook::Middle;

	}
	if (true == GameEngineInput::IsDown('W'))
	{
		Look = PlayerLook::Up;
		
	}
	if (true == GameEngineInput::IsDown('S') && true == GetIsOnAir())
	{
		Look = PlayerLook::Down;
	}


	if (true == GameEngineInput::IsPress('A') && true == GameEngineInput::IsUp('D') /*&& Dir == PlayerDir::Right*/)
	{
		CheckDir = PlayerDir::Left;
	}

	if (true == GameEngineInput::IsPress('D') && true == GameEngineInput::IsUp('A') /*&& Dir == PlayerDir::Left*/)
	{
		CheckDir = PlayerDir::Right;
	}


	if (CheckDir != PlayerDir::Max)
	{
		ChangeDir = true;
		Dir = CheckDir;
	}

	if (CheckDir != PlayerDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}

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

		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::Jump_Arms));

		if (Dir == PlayerDir::Left)
		{
			ArmRenderer->SetRenderPos({ 30,-4 });
		}
		else if (Dir == PlayerDir::Right)
		{
			ArmRenderer->SetRenderPos({ 30,4 });
		}
		ArmRenderer->ChangeAnimation(AnimationName + "Up_Arm");
		break;
	case PlayerLook::Middle:

		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::Nomal_Arms));
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
		ArmRenderer->SetOrder(static_cast<int>(RenderOrder::Jump_Arms));
		if (Dir == PlayerDir::Left)
		{
			ArmRenderer->SetRenderPos({ -34,-4 });
		}
		else if (Dir == PlayerDir::Right)
		{
			ArmRenderer->SetRenderPos({ 30,-4 });
		}
		ArmRenderer->ChangeAnimation(AnimationName + "Down_Arm");
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
