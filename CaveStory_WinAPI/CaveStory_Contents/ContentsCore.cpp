#include "ContentsCore.h"
#include"TitleLevel.h"
#include"FirstCave_startPointLevel.h"
#include "EndingLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 200,30 }, { 1280, 960 });
	
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<FirstCave_StartPointLevel>("FirstCave_StartPointLevel");
	//GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");


	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
}


void ContentsCore::Release()
{
}
