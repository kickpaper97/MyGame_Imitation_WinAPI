#include<GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCore.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/GameEngineActor.h>



#include "TitleLevel.h"
#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.5f);
	GameEngineWindow::MainWindow.CursorOff();

	BackGround* Back = CreateActor<BackGround>();
	Back->Init("bkMoon.Bmp", 2);
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());


	float4 TitlePos = GameEngineWindow::MainWindow.GetScale().Half();
	TitlePos.Y *= 0.5;

	BackGround* Title = CreateActor<BackGround>();
	Title->Init("Title.Bmp", 2);
	Title->SetPos(TitlePos);




	if (nullptr == GameEngineSound::FindSound("Title.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Title.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("menu_move.wav"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("menu_select.wav"));


	}

	BackGround* StartButton = CreateActor<BackGround>();
	StartButton->Init("StartButton.Bmp", 2);
	StartButton->SetPos({ GameEngineWindow::MainWindow.GetScale().Half().X, GameEngineWindow::MainWindow.GetScale().Half().Half().Y*3});
	
	Select = CreateActor<BackGround>();
	Select->Init("Select.Bmp", 2);
	Select->SetPos({ GameEngineWindow::MainWindow.GetScale().Half().X-200.0f, GameEngineWindow::MainWindow.GetScale().Half().Half().Y * 3 });


}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown(VK_UP))
	{
		--MenuSelect;
		MenuSelectSound.SetVolume(2.0f);
		MenuSelectSound = GameEngineSound::SoundPlay("menu_move.wav");
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		++MenuSelect;;
		MenuSelectSound.SetVolume(2.0f);
		MenuSelectSound = GameEngineSound::SoundPlay("menu_move.wav");

	}

	if (0 == MenuSelect)
	{
		Select->GetRenderer()->Off();
	}
	else if (1 == MenuSelect)
	{
		Select->GetRenderer()->On();
	}


	if (2 <= MenuSelect)
	{
		MenuSelect = 0;
	}
	if (0 > MenuSelect)
	{
		MenuSelect = 1;
	}

	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		if (MenuSelect == 1)
		{
			MenuSelectSound = GameEngineSound::SoundPlay("menu_select.wav");

			GameEngineCore::ChangeLevel("Arthur_sHouse");
		}
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		GameEngineCore::ChangeLevel("EggCorridor");
	}

	


}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	 BGMPlayer = GameEngineSound::SoundPlay("Title.mp3");
	BGMPlayer.SetLoop(10000);
}



void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
	BGMPlayer.Stop();
}
