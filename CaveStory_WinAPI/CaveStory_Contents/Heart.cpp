#include "Heart.h"
#include"player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Heart.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Heart.Bmp"), 2, 1);

	}
	{
		Renderer = CreateRenderer(RenderOrder::Bullet);
		Renderer->CreateAnimation("Heart", "Heart.Bmp", 0, 1, 0.1f, true);
		Renderer->SetRenderPos({ 0,-20 });
		Renderer->ChangeAnimation("Heart");


	}
	{
		Collision = CreateCollision(CollisionOrder::Heart);
		Collision->SetCollisionType(CollisionType::Rect);
		Collision->SetCollisionScale({ 50,32 });
		Collision->SetCollisionPos({ 2,-28 });
	}


}

void Heart::Update(float _Delta)
{
	if (2.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			// Death();


			Death();
		}
	}

	if (1.5f < GetLiveTime())
	{
		if (true == IsUpdate())
		{
			Renderer->Off();
		}
		else
		{
			Renderer->On();
		}
	}



	if (this->Collision != nullptr)

	{
		std::vector<GameEngineCollision*> _Col;
		if (true == Collision->Collision(CollisionOrder::PlayerBody, _Col, CollisionType::CirCle, CollisionType::Rect))
		{
			for (size_t i = 0; i < _Col.size(); i++)
			{
				GameEngineCollision* Collison = _Col[i];

				Player* MyPlayer = dynamic_cast<Player*>(Collison->GetActor());

				MyPlayer->SetHp(MyPlayer->GetHp() + HpValue);


				Death();

			}
		}

	}

}
