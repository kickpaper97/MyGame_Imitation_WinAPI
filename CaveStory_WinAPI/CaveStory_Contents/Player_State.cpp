#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#define PlayerSpeed 300.0f




void Player::IdleStart()
{
	

	ChangeAnimationState("Idle");
	
	JumpPower = 0;
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}


void Player::JumpStart()
{
	{
	unsigned int Color = GetGroundColor(RGB(255, 255, 255));

	if (RGB(255, 255, 255) == Color)
	{
		return;
	}

	}

	ChangeAnimationState("Jump");
	SetGravityVector(float4::UP * JumpPower);
	JumpPower = 0;

}
void Player::HoverStart()
{
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
		|| true == GameEngineInput::IsDown(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT)
		)
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
		
	}

	if (true == GameEngineInput::IsUp('Z'))
	{
		if (1.5f <= JumpPower)
		{
			JumpPower = 1.5f;
		}
		else if (1.0 >= JumpPower)
		{
			JumpPower = 1.0f;
		}

		if (0.0f == GetGravityVector().Y)
		{

		DirCheck();
		ChanageState(PlayerState::Jump);


		}
	}

	// 줄줄이 사탕으로 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}


void Player::RunUpdate(float _Delta)
{
	

	

	DirCheck();

	//속도 빠를때 경사로 공중부양 제한
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
		MovePos = { -PlayerSpeed * _Delta, 0.0f };
		

	}
	 if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{

		
		 CheckPos = RightCheck;
		 UpCheck.X = RightCheck.X;
 		MovePos = { PlayerSpeed * _Delta, 0.0f };
		
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
		JumpPower +=_Delta;
		
	}

	if (true == GameEngineInput::IsUp('Z'))
	{
		if (2.5f <= JumpPower)
		{
			JumpPower = 2.5f;
		}
		else if (1.0 >= JumpPower)
		{
			JumpPower = 1.0f;
		}

		if (0.0f == GetGravityVector().Y)
		{

			DirCheck();
			ChanageState(PlayerState::Jump);
			return;


		}
		

	}

	


	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
		return;
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
			MovePos = float4::ZERO;
		}
		
	}
	DirCheck();
}

void Player::JumpUpdate(float _Delta) 
{
	
	
	//float4 JumpPos = float4::ZERO;
	

	DirCheck();
	Gravity(_Delta);


	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		CheckPos = LeftCheck;
		UpCheck.X = LeftCheck.X;
		MovePos = { -PlayerSpeed * _Delta,0.0f };


	}

	if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		CheckPos = RightCheck;
		UpCheck.X = RightCheck.X;
		MovePos = { PlayerSpeed * _Delta, 0.0f };

	}


	{

		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (CeilingColor == RGB(255, 255, 255))
		{
			if (Color == RGB(255, 255, 255))
			{
				if (true == GameEngineInput::IsDown('Z'))
				{
					if (true == CanHover)
					{
						ChanageState(PlayerState::Hover);
						return;
					}
				}
				AddPos(MovePos);
				GetLevel()->GetMainCamera()->AddPos(MovePos);
			}
			else
			{
				DirCheck();
				MovePos = float4::ZERO;
				ChanageState(PlayerState::Idle);
			}
		}
		else
		{
			while (CeilingColor != RGB(255, 255, 255))
			{
				CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
				AddPos(float4::DOWN);

			}

			GravityReset();

		}

	}

			/*AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);*/
	
}

void Player::HoverUpdate(float _Delta)
{
	Gravity(_Delta);
	 static float HoverTime = 1.0f;


	if (true==GameEngineInput::IsPress('Z'))
	{
		if (0.0f <= HoverTime)
		{
			AddGravityVector(float4::UP*_Delta *2.0f);
			HoverTime -= _Delta;

			
		}
		

	}

	DirCheck();

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{


		CheckPos = LeftCheck;
		UpCheck.X = LeftCheck.X;
		MovePos = { -PlayerSpeed * _Delta, 0.0f };


	}
	if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{


		CheckPos = RightCheck;
		UpCheck.X = RightCheck.X;
		MovePos = { PlayerSpeed * _Delta, 0.0f };

	}

		{
			unsigned int Color = GetGroundColor(RGB(255, 255, 255));
			if (RGB(255, 255, 255) != Color)
			{
				HoverTime = 1.0f;
				ChanageState(PlayerState::Idle);
				return;
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
					HoverTime = 0.0f;

				}

				GravityReset();


			}
			else
			{

			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
			}
			
			
		}

}



