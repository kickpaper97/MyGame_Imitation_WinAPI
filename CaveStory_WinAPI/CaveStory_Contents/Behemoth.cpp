#include "Behemoth.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "ContentsEnum.h"
#include "Player.h"

#define NomalSpeed 100.0f
#define AngerSpeed 200.0f

Behemoth::Behemoth()
{
}

Behemoth::~Behemoth()
{
}

void Behemoth::Start()
{
	Monster::Start();

	if (false == ResourcesManager::GetInst().IsLoadTexture("NpcEggs1_Behemoth.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("NpcEggs1_Behemoth.Bmp"), 6, 2);


	}

	{
		Renderer = CreateRenderer(RenderOrder::MiddlePlay);

		Renderer->CreateAnimation("Behemoth_Left_Move", "NpcEggs1_Behemoth.Bmp", 0, 2,0.3f ,true);
		Renderer->CreateAnimation("Behemoth_Right_Move", "NpcEggs1_Behemoth.Bmp", 6, 8, 0.3f,true);

		Renderer->CreateAnimation("Behemoth_Left_Anger", "NpcEggs1_Behemoth.Bmp", 4, 5, 0.2f ,true);
		Renderer->CreateAnimation("Behemoth_Right_Anger", "NpcEggs1_Behemoth.Bmp", 10, 11, 0.2f,true);

		Renderer->CreateAnimation("Behemoth_Left_Damaged", "NpcEggs1_Behemoth.Bmp", 3, 3, 0.2f, false);
		Renderer->CreateAnimation("Behemoth_Right_Damaged", "NpcEggs1_Behemoth.Bmp", 9, 9, 0.2f, false);

		Renderer->ChangeAnimation("behemoth_Left_Move");

	}


	{
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionType(CollisionType::Rect);
		BodyCollision->SetCollisionPos({ 2,-44 });
		BodyCollision->SetCollisionScale({ 114,88 });
	}

	SetHp(16);
	SetMonsterSize(MonsterSize::Max);
	ChanageState(BehemothState::Move);
}
void Behemoth::Update(float _Delta)
{
	Monster::Update(_Delta);








	StateUpdate(_Delta);
}

void Behemoth::Render(float _Delta)
{

}

void Behemoth::ChanageState(BehemothState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case  BehemothState::Move:
			MoveStart();
			break;
		case BehemothState::Anger:
			AngerStart();
			break;
		case BehemothState::Damaged:
			DamagedStart();
		default:
			break;
		}
	}

	State = _State;
}

void Behemoth::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BehemothState::Move:
		return MoveUpdate(_Delta);
		break;
	case BehemothState::Anger:
		return AngerUpdate(_Delta);
		break;
	case BehemothState::Damaged:
		return DamagedUpdate(_Delta);
	default:
		break;
	}

}

void Behemoth::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Behemoth_";

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



void Behemoth::MoveStart()
{
	MovePos = float4::ZERO;
	ChangeAnimationState("Move");
}

void Behemoth::AngerStart()
{
	MovePos = float4::ZERO;

	ChangeAnimationState("Anger");
}

void Behemoth::DamagedStart()
{
}

void Behemoth::MoveUpdate(float _Delta)
{
	
	if (MonsterDir::Left == Dir)
	{
		MovePos = float4::LEFT*NomalSpeed * _Delta;
	}
	else if (MonsterDir::Right == Dir)
	{
		MovePos = float4::RIGHT * NomalSpeed * _Delta;
	}

	if (IsDamaged == true)
	{
		ChanageState(BehemothState::Damaged);
		return;
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

			AddPos(MovePos);
			GravityReset();
		}
	}



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color != RGB(255, 255, 255))
		{
			if (Dir == MonsterDir::Left)
			{
				Dir = MonsterDir::Right;
				BodyCheckPos = RightBodyCheck;
				ChangeAnimationState("Move");
			}
			else if (Dir == MonsterDir::Right)
			{
				Dir = MonsterDir::Left;
				BodyCheckPos = LeftBodyCheck;
				ChangeAnimationState("Move");
			}

		}



	}

	

	GetLevel()->GetMainCamera()->GetPos();
	int a = 0;
	a = 1;

}

void Behemoth::AngerUpdate(float _Delta)
{
	if (MonsterDir::Left == Dir)
	{
		MovePos = float4::LEFT * AngerSpeed * _Delta;
	}
	else if (MonsterDir::Right == Dir)
	{
		MovePos = float4::RIGHT * AngerSpeed * _Delta;
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
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color != RGB(255, 255, 255))
		{
			if (Dir == MonsterDir::Left)
			{
				Dir = MonsterDir::Right;
				BodyCheckPos = RightBodyCheck;
				ChangeAnimationState("Anger");
			}
			else if (Dir == MonsterDir::Right)
			{
				Dir = MonsterDir::Left;
				BodyCheckPos = LeftBodyCheck;
				ChangeAnimationState("Anger");
			}

		}

		AddPos(MovePos);

		

		
	}


}

void Behemoth::DamagedUpdate(float _Delta)
{
	
	MovePos = float4::ZERO;

	static bool FirstIn = true;
	static float InvincibleTime = 0.0f;
	static float RenderChangeTime = 0.0f;
	if (FirstIn)
	{
		switch (static_cast<MonsterSize>(GetMonsterSize()))
		{
		case MonsterSize::Min:
			HurtSound = GameEngineSound::SoundPlay("enemy_hurt_small.wav");
			break;
		case MonsterSize::Mid:
			HurtSound = GameEngineSound::SoundPlay("enemy_hurt.wav");
			break;
		case MonsterSize::Max:
			HurtSound = GameEngineSound::SoundPlay("enemy_hurt_Big.wav");
			break;
		case MonsterSize::None:
			break;
		default:
			break;
		}
		FirstIn = false;
	}


	if (Dir == MonsterDir::Left)
	{
		Renderer->ChangeAnimation("Behemoth_Left_Damaged");

	}
	else if (Dir == MonsterDir::Right)
	{
		Renderer->ChangeAnimation("Behemoth_Right_Damaged");

	}


	if (1.0f < InvincibleTime)
	{
		IsDamaged = false;
		FirstIn = true;
		Renderer->On();
		InvincibleTime = 0.0f;
		ChanageState(BehemothState::Move);
		return;
	}

	{
		if (0.05f < RenderChangeTime)
		{
			if (Renderer->IsUpdate())
			{
				Renderer->Off();
				RenderChangeTime = 0.0f;
			}
			else
			{
				Renderer->On();
				RenderChangeTime = 0.0f;

			}
		}
		RenderChangeTime += _Delta;
	}

	InvincibleTime += _Delta;


	
}

