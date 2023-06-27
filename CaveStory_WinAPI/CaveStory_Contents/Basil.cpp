#include "Basil.h"

#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "ContentsEnum.h"
#include "Player.h"


Basil::Basil()
{
}

Basil::~Basil()
{
}

void Basil::Start()
{

}

void Basil::Update(float _Delta)
{
	float4 PlayerDir = Player::GetMainPlayer()->GetPos();
	float4 Dir = PlayerDir - GetPos();
	

	

		

	{
			if (true == Renderer->IsAnimation("Basil_Right"))
		{


		}


		else if(true == Renderer->IsAnimation("Basil_Left"))
		{

		}

	}




	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color == RGB(255, 255, 255))
		{
			//AddPos();

		}
	}

	

}
