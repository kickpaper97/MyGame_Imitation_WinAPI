#include "EggCorridor.h"
#include "ContentsEnum.h"
#include"Monster.h"
#include"MonsterCutter.h"
#include "Basil.h"
#include"BeetleFree.h"
#include"BeetleWall.h"
#include"Behemoth.h"
#include"CureMachine.h"
#include "TelePorter.h"
#include"Door.h"
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

	if (nullptr == GameEngineSound::FindSound("Mischievous_Robot.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Mischievous_Robot.mp3"));


	}

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
	
	LevelPlayer->SetPos({ 360.0f,380.0f });
	

	CreateActor<PlayUIManager>();

	

	
}

void EggCorridor::Update(float _Delta)
{
	Monster::MonsterBoundaryCheck();

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


	BGMPlayer = GameEngineSound::SoundPlay("Mischievous_Robot.mp3");
	BGMPlayer.SetLoop(10000);
	
	
	//Cutter
	{
		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 1450 ,450 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 2250 ,450 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 2450 ,450 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 2650 ,500 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 2850 ,500 });
		}
		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 2950 ,500 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 3350 ,450 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 3750 ,300 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{ 3935 ,270 });
		}

		{
			Monster* NewMonster = CreateActor<MonsterCutter>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

			NewMonster->SetPos(float4{6050 ,500 });
		}
	}
	

	{
		Monster* NewMonster = CreateActor<Basil>();
		NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");

	}
	
	//BeetheFree
	{

		{
			Monster* newMonster = CreateActor<BeetleFree>();
			newMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			newMonster->SetPos({ 2350.0f,280.0f });

		}



		{
			Monster* newMonster = CreateActor<BeetleFree>();
			newMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			newMonster->SetPos({ 4150.0f,200.0f });

		}

		{
			Monster* newMonster = CreateActor<BeetleFree>();
			newMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			newMonster->SetPos({ 4250.0f,300.0f });

		}

		{
			Monster* newMonster = CreateActor<BeetleFree>();
			newMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			newMonster->SetPos({ 6450.0f,250.0f });

		}

	}

	//BeetleWall
	{
		{
			Monster* NewMonster = CreateActor<BeetleWall>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({ 300.0f,200.0f });
		}

		{
			Monster* NewMonster = CreateActor<BeetleWall>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({5060.0f,500.0f });
		}

		{
			Monster* NewMonster = CreateActor<BeetleWall>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({7890.0f,550.0f });
		}


	}
	


	//Behemoth
	{ 
		{
			Monster* NewMonster = CreateActor<Behemoth>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({ 730 ,470 });
		}

		{
			Monster* NewMonster = CreateActor<Behemoth>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({ 1670 ,470 });
		}

		{
			Monster* NewMonster = CreateActor<Behemoth>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({ 1830 ,470 });
		}


		{
			Monster* NewMonster = CreateActor<Behemoth>();
			NewMonster->SetGroundTexture("EggCorridor_Ground.Bmp");
			NewMonster->SetPos({ 6000 ,470 });
		}

	}


	

	{
		CureMachine* NewCure = CreateActor<CureMachine>(RenderOrder::MiddlePlay);
		NewCure->SetPos({ 550,420 });
	}

	{
		TelePorter* NewTeleporter = CreateActor<TelePorter>();
		NewTeleporter->SetPos({ 360.0f,388.0f });
		NewTeleporter->SetDestination("Arthur_sHouse");
		
	}

	{
		Door* NewDoor = CreateActor<Door>();
		NewDoor->SetPos({ 8032.0f,780 });
	}


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y

}

void EggCorridor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
	Monster::AllMonsterDeath();
}