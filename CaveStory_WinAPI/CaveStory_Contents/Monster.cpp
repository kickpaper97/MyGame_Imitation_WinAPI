#include "Monster.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"
#include"Bullet.h"

std::list<Monster*> Monster::AllMonster;


Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{
	Release();
}



void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
		
	}

	AllMonster.clear();
}


void Monster::Update(float _Delta)
{
	
	

	// Player::MainPlayer = nullptr;
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("몬스터의 충돌체가 설정 되지 않았습니다.");
		return;
	}

	if (nullptr == Renderer)
	{
		MsgBoxAssert("몬스터의 렌더러가 설정 되지 않았습니다.");
		return;
	}


	
	 if (0 >= Hp)
	 {
		 Death();
		 
	 }


	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::Bullet, _Col, CollisionType::CirCle, CollisionType::Rect))
	{
		for (size_t i = 0; i <_Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Bullet* HitBullet = dynamic_cast<Bullet*>(Collison->GetActor());

			 Hp-=HitBullet->GetDamage();
			 HitBullet->Death();
			
		}
	}

}

void Monster::Start()
{
	SetPlayerPos(Player::GetMainPlayer()->GetPos());
	float4 Dir = GetPlayerPos() - GetPos();

	if (GameEngineWindow::MainWindow.GetScale().Size() < Dir.Size())
	{
		Off();
	}

}

void Monster::Release()
{
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

		if (nullptr == Monster)
		{
			MsgBoxAssert("nullptr인 랜더러가 레벨의 리스트에 들어가 있었습니다.");
			continue;
		}
		// [s] [a] [a]     [a] [e]
		MonStartIter = AllMonster.erase(MonStartIter);

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
