#include "EndingLevel.h"
#include "BackGround.h"
#include<GameEnginePlatform/GameEngineWindow.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}

void EndingLevel::Start()
{

	if (nullptr == GameEngineSound::FindSound("Ending.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Ending.mp3"));


	}

	BackGround* Back = CreateActor<BackGround>();
	Back->Init("Ending.Bmp", 2);
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());
}

void EndingLevel::Update(float _DeltaTime)
{
}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

	ShowCursor(TRUE);
	BGMPlayer.SetVolume(0.3f);
	BGMPlayer = GameEngineSound::SoundPlay("Ending.mp3");
	BGMPlayer.SetLoop(1000);
}
