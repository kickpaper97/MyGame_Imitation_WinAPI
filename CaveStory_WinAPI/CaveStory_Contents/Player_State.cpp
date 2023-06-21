#include "Player.h"
#include "HoverEffect.h"
#include"QuestionMark.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#define SpeedLimit 300.0f
#define JumpTimeLimit 0.6f



void Player::IdleStart()
{
	MovePos = float4::ZERO;

	ChangeAnimationState("Idle");
	
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

}
void Player::HoverStart()
{
	
}

void Player::SearchStart()
{
	if (false == CanSearch)
	{
		ChanageState(PlayerState::Idle);
		return;
	}
	ChangeAnimationState("Back");
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
		DirCheck();
		ChanageState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		ChanageState(PlayerState::Search);
		return;
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
		float4 CheckPos = float4::DOWN;
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

	{
	//static float PlayerSpeed =0.0f;

	if (true == GameEngineInput::IsPress(VK_LEFT)&&Dir==PlayerDir::Left)
		{
			//PlayerSpeed +=_Delta*100;

		
			BodyCheckPos = LeftBodyCheck;
			UpCheck.X = LeftHeadCheck.X;
			MovePos = { -SpeedLimit * _Delta, 0.0f };
		

		}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
		{
			//PlayerSpeed += _Delta*100;
		
		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
 			MovePos = { SpeedLimit * _Delta, 0.0f };
		
		}
	else
	 {
		 MovePos = float4::ZERO;

	 }
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
			DirCheck();
			ChanageState(PlayerState::Jump);
			return;

	}

	


	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
		return;
	}

	{
		
		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);
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
	
	
	float4 JumpVector= float4::UP;
	JumpVector.Normalize();

	static float DeltaCheck= 0.0f;


	if (JumpTimeLimit > DeltaCheck)
	{
		if (true == GameEngineInput::IsPress('Z'))
			{

				AddPos(JumpVector * _Delta * 500.0f);
				DeltaCheck += _Delta;
				if (JumpTimeLimit <= DeltaCheck)
				{
					GravityReset();
				}
		
			}

		if (true == GameEngineInput::IsUp('Z'))
		{
			GravityReset();
			
			DeltaCheck = 10.0f;
		}


	}
	
	DirCheck();

	//static float PlayerSpeed = 0.0f;

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		//PlayerSpeed += _Delta;

		BodyCheckPos = LeftBodyCheck;
		UpCheck.X = LeftHeadCheck.X;
		MovePos = { -SpeedLimit * _Delta,0.0f };


	}else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		//PlayerSpeed += _Delta;

		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
		MovePos = { SpeedLimit * _Delta, 0.0f };

	}
	else
	{
		MovePos = float4::ZERO;

	}
	

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);

			if (true == GameEngineInput::IsDown('Z'))
			{
				if (true == CanHover)
				{
					DeltaCheck = 0.0f;
					GravityReset();
					ChanageState(PlayerState::Hover);
					return;
				}
			}

		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			DeltaCheck = 0.0f;
			ChanageState(PlayerState::Idle);
			return;
		}

	}

	{

			unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
			unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);

			if (CeilingColor != RGB(255, 255, 255))
			{
			
				while (CeilingColor != RGB(255, 255, 255))
				{
					CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
					AddPos(float4::DOWN);

				}

				GravityReset();
				DeltaCheck = 10.0f;

			}
	}



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);

		}
	}


	
	
}

void Player::HoverUpdate(float _Delta)
{
	  static float HoverTime = 1.0f;
	  static float HoverRespawnTime = 0.0f;
	  
	
	

	

	if (true == GameEngineInput::IsPress('Z'))
	{
		if (0.0f < HoverTime)
		{
			
			AddGravityVector(float4::UP * _Delta * 2.8f);

			if (0.2f <= HoverRespawnTime)
			{

				HoverEffect* NewHoverEffect = GetLevel()->CreateActor<HoverEffect>(RenderOrder::BackPlay);
				NewHoverEffect->SetPos(GetPos());
				HoverRespawnTime = 0.0f;
			}



			HoverRespawnTime += _Delta;
			HoverTime -= _Delta;


		}


	}

	DirCheck();
	//static float PlayerSpeed = 0.0f;

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		//PlayerSpeed += _Delta*10;

		BodyCheckPos = LeftBodyCheck;
		UpCheck.X = LeftHeadCheck.X;
		MovePos = { -SpeedLimit * _Delta, 0.0f };


	}else
	if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		//PlayerSpeed += _Delta*10;

		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
		MovePos = { SpeedLimit * _Delta, 0.0f };

	}
	else
	{
		MovePos = float4::ZERO;

	}


		{
			unsigned int Color = GetGroundColor(RGB(255, 255, 255));
			if (RGB(255, 255, 255) != Color)
			{
			


				HoverTime = 1.0f;
				ChanageState(PlayerState::Idle);
				return;
			}
			else
			{

				Gravity(_Delta);

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
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);
		

		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);

		}
	}



			
}

void Player::SearchUpdate(float _Delta)
{

	if (true == CanSearch)
	{
	QuestionMark* NewQuestionMark = GetLevel()->CreateActor<QuestionMark>(RenderOrder::FrontPlay);
	
	NewQuestionMark->SetPos(GetPos());
	NewQuestionMark->AddPos({ 0,-40 });

	}
	
	
	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT)
		)
	{
		CanSearch = true;
		ChanageState(PlayerState::Idle);
		return;
	}
	CanSearch = false;

}

