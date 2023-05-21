#include "ContentsCore.h"
#include"TitleLevel.h"
#include"PlayLevel.h"
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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<PlayLevel>("EndingLevel");


	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
}

void ContentsCore::Render()
{
}

void ContentsCore::Release()
{
}
