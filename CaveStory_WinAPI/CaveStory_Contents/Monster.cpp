#include "Monster.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "Player.h"
#include"Bullet.h"
#include "ExpBall.h"
#include"Heart.h"

std::list<Monster*> Monster::AllMonster;
enum class ::MonsterDir;

Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{
	
	

}



void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
		
	}

	AllMonster.clear();
}


void Monster::Drop()
{
	int Rand = GameEngineRandom::MainRandom.RandomInt(0, 1);

		switch (Rand)
		{
		case 0:
		
			for (size_t i = 0; i < 3; i++)
			{
			ExpBall* NewExpball = GetLevel()->CreateActor<ExpBall>(RenderOrder::MiddlePlay);
			NewExpball->SetGroundTexture(Player::GetMainPlayer()->GetGroundTexture());
			NewExpball->SetBallType(MonSize);
			NewExpball->SetPos({GetPos().X,GetPos().Y-10.0f});

			}
			
			break;

		case 1:

		{
			Heart* NewHeart = GetLevel()->CreateActor<Heart>(RenderOrder::MiddlePlay);
			NewHeart->SetPos(GetPos());

		}

			break;

		default:
			break;
		}

}

void Monster::Update(float _Delta)
{
	
	

	// Player::MainPlayer = nullptr;
	

	if (nullptr == Renderer)
	{
		MsgBoxAssert("몬스터의 렌더러가 설정 되지 않았습니다.");
		return;
	}

	if (MonsterSize::None == MonSize)
	{
		MsgBoxAssert("몬스터의 크기가 정해지지 않았습니다.");
		return;
	}


	if (IsDamaged == true)
	{
		Damaged(_Delta);
		
		

	}

	
	 if (0 >= GetHp())
	 {
		 Death();
		
		 Drop();

		 std::list<Monster*>::iterator MonStartIter = AllMonster.begin();
		 	std::list<Monster*>::iterator MonEndIter = AllMonster.end();
		 
		 	for (; MonStartIter != MonEndIter; )
		 	{
		 		Monster* Monster = *MonStartIter;
		 		
		 
		 		if (false == Monster->IsDeath())
		 		{
		 			++MonStartIter;
		 			continue;
		 		}
		 
		 		// [s] [a] [a]     [a] [e]
		 		MonStartIter = AllMonster.erase(MonStartIter);
		 
		 	}

		 
	 }

	 if (this->BodyCollision != nullptr)
	 {
		std::vector<GameEngineCollision*> _Col;
		if (true == BodyCollision->Collision(CollisionOrder::Bullet, _Col, CollisionType::CirCle, CollisionType::Rect))
		{
			for (size_t i = 0; i <_Col.size(); i++)
			{
				GameEngineCollision* Collison = _Col[i];

				Bullet* HitBullet = dynamic_cast<Bullet*>(Collison->GetActor());

				

				 SetHp(GetHp()- HitBullet->GetDamage());
				 IsDamaged = true;
				 HitBullet->Death();
			
			}
		}

	 }

}

void Monster::Start()
{

	if (nullptr == GameEngineSound::FindSound("enemy_hurt.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("enemy_hurt_small.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("enemy_hurt_Big.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("enemy_hurt.wav"));

	}

	SetPlayerPos(Player::GetMainPlayer()->GetPos());
	float4 Dir = GetPlayerPos() - GetPos();

	if (GameEngineWindow::MainWindow.GetScale().Size() < Dir.Size())
	{
		Off();
	}





}


void Monster::MonsterBoundaryCheck()
{


	for (Monster* Monster : AllMonster)
	{
		Monster->SetPlayerPos(Player::GetMainPlayer()->GetPos());
		float4 Dir = Monster->GetPlayerPos() -Monster-> GetPos();
		
		
		
		if (false == Monster->IsUpdate())
		{

			if (GameEngineWindow::MainWindow.GetScale().Size() >= Dir.Size())
			{
				Monster->On();
			}
		}
		else
		{
			if (GameEngineWindow::MainWindow.GetScale().Size() < Dir.Size())
			{
				Monster->Off();
				continue;
			}
		}
	}
}

void Monster::Damaged(float _Delta)
{
	

	static bool FirstIn = true;
	static float InvincibleTime = 0.0f;
	static float RenderChangeTime = 0.0f;
	if (FirstIn)
	{
		switch (MonSize)
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

	if (1.0f < InvincibleTime)
	{
		IsDamaged = false;
		FirstIn = true;
		Renderer->On();
		InvincibleTime = 0.0f;
		return;
	}

	{
		if (0.05f< RenderChangeTime)
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