#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}


void Player::JumpStart()
{
	IsJump = true;
	ChangeAnimationState("Jump");
}


void Player::IdleUpdate(float _Delta)
{

	///////////////Gravity
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
		}
	}


	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT))
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		JumpPower = 0.0f;

	}

	if (true == GameEngineInput::IsPress('Z'))
	{
		JumpPower +=_Delta;
		if (1.0f <= JumpPower)
		{
			JumpPower = 1.5f;
		}
	}

	if (true == GameEngineInput::IsUp('Z'))
	{
		if (0.3 >= JumpPower)
		{
			JumpPower = 0.3f;
		}

		IsJump = true;
		DirCheck();
		ChanageState(PlayerState::Jump);
		

	}

	// 줄줄이 사탕으로 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}


void Player::RunUpdate(float _Delta)
{
	float Speed = 300.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = UpCheck;

	DirCheck();
	if (0.0f <= GetGravityVector().Y)
	{
		CheckPos = float4::DOWN;
		int CountCheck = 0;
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		while (RGB(255, 255, 255) != Color)
		{
			CheckPos += float4::DOWN;
			Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
			++CountCheck;
		}

		if (3 > CountCheck)
		{
			SetPos(GetPos() + CheckPos);
		}

		CheckPos = UpCheck;
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
		}

	}

	if (true == GameEngineInput::IsPress(VK_LEFT)&&Dir==PlayerDir::Left)
	{
		CheckPos = LeftCheck;
		UpCheck.X = LeftCheck.X;
		MovePos = { -Speed * _Delta, 0.0f };
		

	}

	 if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		 CheckPos = RightCheck;
		 UpCheck.X = RightCheck.X;
 		MovePos = { Speed * _Delta, 0.0f };
		
	}

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		Look = PlayerLook::Up;
		
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		Look= PlayerLook::Down;
		
	}


	if (true == GameEngineInput::IsDown('Z'))
	{
		JumpPower = 0.0f;
		
	}

	if (true == GameEngineInput::IsPress('Z'))
	{
		if (1.0f <= JumpPower)
		{
			JumpPower = 1.5f;
		}
		JumpPower +=_Delta;
	}

	if (true == GameEngineInput::IsUp('Z'))
	{

		if (0.5 >= JumpPower)
		{
			JumpPower = 0.5f;
		}
		IsJump = true;
		DirCheck();
		ChanageState(PlayerState::Jump);
		

	}

	


	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
	}
	else

	{
		
		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		if(CeilingColor== RGB(255, 255, 255))
		{
			if (Color == RGB(255, 255, 255))
			{
				AddPos(MovePos);
				GetLevel()->GetMainCamera()->AddPos(MovePos);
			}
		}
		
	}

}

void Player::JumpUpdate(float _Delta) 
{
	if (false == IsJump)
	{
		return;
	}
	float Speed = 300.0f;
	float4 JumpPos = float4::ZERO;


	DirCheck();
	JumpPos = float4::UP * JumpPower *_Delta* Speed;
	{

		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck );
		
		if (CeilingColor == RGB(255, 255, 255))
		{
			AddPos(JumpPos);
		}
		else
		{
			while (CeilingColor != RGB(255, 255, 255))
			{
				CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
				AddPos(float4::DOWN);
				
			}
			
			JumpPower = 0;
			GravityReset();
			
			
			float4 posi=GetPos();
			int a = 0;
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
			GravityReset();
			IsJump = false;
		
			DirCheck();
			ChanageState(PlayerState::Idle);
		}
	}
}


