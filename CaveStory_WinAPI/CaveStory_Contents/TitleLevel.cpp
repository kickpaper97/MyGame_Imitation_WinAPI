#include<GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCore.h>
#include<GameEnginePlatform/GameEngineWindow.h>



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
	

	BackGround* Back = CreateActor<BackGround>();
	Back->Init("bkMoon.Bmp",2);
	Back->SetPos(GameEngineWindow::MainWindow.GetScale().Half());


	float4 TitlePos = GameEngineWindow::MainWindow.GetScale().Half();
	TitlePos.Y *= 0.5;

	BackGround* Title = CreateActor<BackGround>();
	Title->Init("Title.Bmp", 2);
	Title->SetPos(TitlePos);



}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}
