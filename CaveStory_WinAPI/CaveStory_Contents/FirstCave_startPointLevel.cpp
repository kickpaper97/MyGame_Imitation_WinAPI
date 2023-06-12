#include "FirstCave_startPointLevel.h"
#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include<GameEngineCore/ResourcesManager.h>



#include"Player.h"
#include "BackGround.h"

FirstCave_StartPointLevel::FirstCave_StartPointLevel()
{
}

FirstCave_StartPointLevel::~FirstCave_StartPointLevel()
{
}

void FirstCave_StartPointLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Col_FirstCave_StartPoint.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Col_FirstCave_StartPoint.Bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("FirstCave_StartPoint.Bmp","Col_FirstCave_StartPoint.Bmp");
	

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Col_FirstCave_StartPoint.Bmp");
	LevelPlayer->SetActorBoundery("FirstCave_StartPoint.Bmp");
	LevelPlayer->SetPos(float4{925 ,500 });

	
}

void FirstCave_StartPointLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}
}


void FirstCave_StartPointLevel::Release()
{
}


void FirstCave_StartPointLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}


	LevelPlayer->SetGroundTexture("Col_FirstCave_StartPoint.Bmp");
	LevelPlayer->SetActorBoundery("FirstCave_StartPoint.Bmp");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y

}

void FirstCave_StartPointLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}