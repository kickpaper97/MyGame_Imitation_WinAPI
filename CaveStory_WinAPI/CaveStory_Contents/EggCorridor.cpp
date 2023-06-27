#include "EggCorridor.h"
#include "ContentsEnum.h"
#include"Monster.h"
#include"MonsterCutter.h"
#include"CureMachine.h"
#include"PlayUIManager.h"

#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>



#include"Player.h"
#include "BackGround.h"
EggCorridor::EggCorridor()
{
}

EggCorridor::~EggCorridor()
{
}

void EggCorridor::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("EggCorridor_Ground.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Map");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EggCorridor_Ground.Bmp"));
	}



	BackGround* FrontPtr = CreateActor<BackGround>(RenderOrder::FrontGround);
	FrontPtr->Init("EggCorridor_Front.Bmp");
	
	
	

	MiddlePtr = CreateActor<BackGround>(RenderOrder::BackGround);
	MiddlePtr->Init("EggCorridor_Middle.Bmp", "EggCorridor_Ground.Bmp");

	LevelPlayer = CreateActor<Player>(RenderOrder::MiddlePlay);

	LevelPlayer->SetGroundTexture("EggCorridor_Ground.Bmp");
	LevelPlayer->SetActorBoundery("EggCorridor_Middle.Bmp");
	LevelPlayer->SetPos(float4{ 925 ,500 });


	CreateActor<PlayUIManager>();

	

	
}

void EggCorridor::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	if (true == GameEngineInput::IsDown('J'))
	{
		MiddlePtr->SwitchRender();
	}
	if (true == GameEngineInput::IsDown('Q'))
	{
		if (PlayUIManager::UI->GetTextBoxIsUpdate())
		{
			PlayUIManager::UI->TextBoxOff();

		}
		else
		{

		PlayUIManager::UI->TextBoxOn();
		}

	}

}


void EggCorridor::Release()
{
}


void EggCorridor::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}


	LevelPlayer->SetGroundTexture("EggCorridor_Ground.Bmp");
	LevelPlayer->SetActorBoundery("EggCorridor_Middle.Bmp");


	{
		Monster* NewMonster = CreateActor<MonsterCutter>();
		NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

		NewMonster->SetPos(float4{ 1200 ,300 });
	}

	{
		CureMachine* NewCure = CreateActor<CureMachine>(RenderOrder::MiddlePlay);
		NewCure->SetPos({ 1000,400 });
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y

}

void EggCorridor::LevelEnd(GameEngineLevel* _NextLevel)
{

}