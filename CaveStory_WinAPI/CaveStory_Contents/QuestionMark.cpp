#include "QuestionMark.h"
#include"ContentsEnum.h"
#include<GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "player.h"

QuestionMark::QuestionMark()
{
}

QuestionMark::~QuestionMark()
{
}

void QuestionMark::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("QuestionMark.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("QuestionMark.Bmp"));

	}
	{
		 Renderer = CreateRenderer("QuestionMark.Bmp",RenderOrder::FrontPlay);
		
		
		
	}

	CreatePos = Player::GetMainPlayer()->GetPos();
	
}

void QuestionMark::Update(float _Delta)
{
	
	
	if (1.0f <= TimeCount)
	{
		
		Death();
	}

	
	if (90.0f>CreatePos.Y-GetPos().Y)
	{
		float pos = CreatePos.Y - GetPos().Y;
		AddPos(float4::UP*2);
	}

	TimeCount += _Delta;

}
