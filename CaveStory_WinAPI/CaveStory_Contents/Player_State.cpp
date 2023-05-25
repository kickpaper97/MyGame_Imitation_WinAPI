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


	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
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

	MovePos = float4::ZERO;

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

	DirCheck();
	if (true == GameEngineInput::IsPress('A')&&Dir==PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		

	}

	 if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
 		MovePos = { Speed * _Delta, 0.0f };
		
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		Look = PlayerLook::Up;
		
	}

	if (true == GameEngineInput::IsPress('S'))
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

		if (0.3 >= JumpPower)
		{
			JumpPower = 0.3f;
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

	
	AddPos(MovePos);
	
	GetLevel()->GetMainCamera()->AddPos(MovePos);


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

	
	AddPos(JumpPos+MovePos);
	

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


